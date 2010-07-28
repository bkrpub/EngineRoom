/*
 *  $Id: tracer.c 755 2009-02-02 12:18:17Z bkr $
 */

#define __TRACER_C__ 1

#include "tracer.h"
#include "er_compat.h"

#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#ifdef __APPLE__

#include <mach-o/dyld.h>
#include <mach-o/loader.h>
#include <mach-o/arch.h>
#include <mach-o/getsect.h>
#include <mach-o/ldsyms.h>
#include <mach-o/nlist.h>
#include <mach-o/stab.h>
#include <mach-o/fat.h>
#include <arpa/inet.h> /* for ntohl */

#define tracerMessage(fmt, ...)          utilMessage(fmt, ## __VA_ARGS__ )
#define tracerReturnWithMessage(ret, fmt, ...) utilReturnWithMessage(ret, fmt, ## __VA_ARGS__)

#define tracerDebug(fmt, ...)          utilDebugIf(TRACER_DEBUG, fmt, ## __VA_ARGS__ )
#define tracerDebugFat(fmt, ...)       utilDebugIf(TRACER_DEBUG_FAT, fmt, ## __VA_ARGS__ )
#define tracerDebugMachO(fmt, ...)     utilDebugIf(TRACER_DEBUG_MACHO, fmt, ## __VA_ARGS__ )
#define tracerDebugSym(fmt, ...)       utilDebugIf(TRACER_DEBUG_SYM, fmt, ## __VA_ARGS__ )
#define tracerDebugSymHeavy(fmt, ...)  utilDebugIf(TRACER_DEBUG_SYM_HEAVY, fmt, ## __VA_ARGS__ )
#define tracerDebugStore(fmt, ...)     utilDebugIf(TRACER_DEBUG_STORE, fmt, ## __VA_ARGS__ )
#define tracerDebugLookup(fmt, ...)    utilDebugIf(TRACER_DEBUG_LOOKUP, fmt, ## __VA_ARGS__ )

#define TRACER_STORE_OR_RETURN(store,ret)  if( NULL == (store) ) tracerReturnWithMessage(ret, \
"attempt to use %s() with NULL store - returning %s", __PRETTY_FUNCTION__, #ret)


int UTIL_NO_INSTRUMENT 
backtrace_via_builtin_return_address(void **pcs, int size)
{
	/* gcc docs say __builtin_return_address(>0) are only for debugging - well, I guess that's what we do... */
	/* __builtin_return_address needs a constant parameter */
#define RETADDR(n) case n: pc = __builtin_return_address(n); break
#define RETBLK8(m) RETADDR(8*m+0); RETADDR(8*m+1); RETADDR(8*m+2); RETADDR(8*m+3); RETADDR(8*m+4); RETADDR(8*m+5); RETADDR(8*m+6); RETADDR(8*m+7) 
	
	int i;
	for( i = 0 ; i < size ; ++i ) {
		void *pc = NULL;
		switch(i) { RETBLK8(0); RETBLK8(1); RETBLK8(2); RETBLK8(3); RETBLK8(4); RETBLK8(5); RETBLK8(6); RETBLK8(7); }
		
		if( pc < (void*) 0x10 ) // on at least 10.5 there is a weird connection between main()s argc and the last frame - better skip it
			break;
		
		pcs[i] = pc;
	}
	
	return i;
}

int UTIL_NO_INSTRUMENT 
tracerAnalyzeFile(UTIL_MACH_HEADER *mhp, const char *imagePath, intptr_t slide, TRACER_SYMBOL_WORKER symbolAction, void *symbolActionInfo, uint64_t options)
{
	size_t imageLength;
	void *image = util_map_image(imagePath, &imageLength);
	
	uint32_t firstMagic = * (uint32_t *) image;
	
	struct mach_header *mhp32 = NULL;
	struct mach_header_64 *mhp64 = NULL;
	
	tracerDebug("Image: %s firstMagic: 0x%08x", strrchr(imagePath, UTIL_PATH_SEPARATOR) ? strrchr(imagePath, UTIL_PATH_SEPARATOR)+1 : imagePath , firstMagic);
	
#if TRACER_DEBUG_FAT
	const NXArchInfo *localArchInfo = NXGetLocalArchInfo();
	const NXArchInfo *currentArchInfo = NXGetArchInfoFromCpuType(mhp->cputype, mhp->cpusubtype);
	tracerDebugFat("local   arch: %s (%s)", localArchInfo->name, localArchInfo->description); 
	tracerDebugFat("current arch: %s (%s)", currentArchInfo->name, currentArchInfo->description); 
#endif
	
	switch ( firstMagic ) {
			
		case FAT_MAGIC:
		case FAT_CIGAM:
		{
			struct fat_header *fat = (struct fat_header *) image;
			
			uint32_t nfat_arch = ntohl( fat->nfat_arch ); /* fat headers are always big endian */
			
			tracerDebugFat("number of architectures in file: %d", nfat_arch);
			
			struct fat_arch *swappedArches = malloc( sizeof(struct fat_arch) * nfat_arch );
			
			if( NULL == swappedArches )
				tracerReturnWithMessage(TRACER_FAILURE, "could not malloc memory for %u fat_arch structs - failing", nfat_arch);
			
			/* arch headers start directly after fat header */
			memcpy( swappedArches, fat + 1, sizeof(struct fat_arch) * nfat_arch );
			
			struct fat_arch *arch = NULL;
			
			uint32_t i;
			for(i = 0 ; i < nfat_arch ; ++i) {
				arch = &swappedArches[i];
				
				arch->cputype = ntohl(arch->cputype);
				arch->cpusubtype = ntohl(arch->cpusubtype);
				arch->offset = ntohl(arch->offset);
				arch->size = ntohl(arch->size);
				arch->align = ntohl(arch->align);
				
				tracerDebugFat("Arch %d @ %p: %d.%d %08x %08x %08x", i, (void*)arch, arch->cputype, arch->cpusubtype, arch->offset, arch->size, arch->align);
			}
			
			arch = NXFindBestFatArch(mhp->cputype, mhp->cpusubtype, swappedArches, nfat_arch);
			
			if ( NULL == arch )
				tracerReturnWithMessage(TRACER_FAILURE, "could not NXFindBestFatArch for (%d.%d) - failing", mhp->cputype, mhp->cpusubtype);
			
			
			tracerDebugFat("best arch @ %p", (void*)arch);
			
			if( arch->cputype & CPU_ARCH_ABI64 ) {
				mhp64 = (struct mach_header_64 *) ((char *) image + arch->offset);
				tracerDebugFat("using 64bit header from fat file");
			} else {
				mhp32 = (struct mach_header *) ((char *) image + arch->offset);
				tracerDebugFat("using 32bit header from fat file");
			}	
			
			break;
		}
			
		case MH_MAGIC_64:
			mhp64 = image;
			tracerDebugFat("using 64bit header from thin file");
			break;
			
		case MH_MAGIC:
			mhp32 = image;
			tracerDebugFat("using 32bit header from thin file");
			break;
			
		default:
			tracerReturnWithMessage(TRACER_FAILURE, "could not find mach_header in %s - firstMagic = 0x%08x", imagePath, firstMagic);
			break;
	}
	
#if TRACER_DEBUG_FAT
	const NXArchInfo *chosenArchInfo = 
	mhp64 ? NXGetArchInfoFromCpuType(mhp64->cputype, mhp64->cpusubtype) : NXGetArchInfoFromCpuType(mhp32->cputype, mhp32->cpusubtype);
	tracerDebugFat("chosen  arch: %s (%s)", chosenArchInfo->name, chosenArchInfo->description); 
#endif
	
	int ret = tracerAnalyzeMachO(mhp64 ? (UTIL_MACH_HEADER *)mhp64 : (UTIL_MACH_HEADER *)mhp32, imagePath, mhp, symbolAction, symbolActionInfo, options);
	
	util_unmap_image(image, imageLength);
	
	return ret;
}

int UTIL_NO_INSTRUMENT 
tracerAnalyzeMachO(UTIL_MACH_HEADER *mhp, const char *imagePath, UTIL_MACH_HEADER *live_mhp, TRACER_SYMBOL_WORKER symbolAction, void *symbolActionInfo, uint64_t options )
{
	tracerDebugMachO("mhp %p live_mhp %p filetype: %u ncmds: %u flags: 0x%08x", 
					 (void*)mhp, (void *)live_mhp, mhp->filetype, mhp->ncmds, (unsigned int)mhp->flags);
	
	int ret = TRACER_SUCCESS;
	
	struct symtab_command *stc = NULL;
	int segmentIndex = 0;
	int pageZeroSegmentIndex = MAX_SECT + 1;
	int textSegmentIndex = MAX_SECT + 1;
	
	unsigned int lcIdx;
	struct load_command *lc = (struct load_command *) (mhp + 1);
	for( lcIdx = 0 ; lcIdx < mhp->ncmds ; lc = (struct load_command *) ((char*) lc + lc->cmdsize), ++lcIdx ) {
		switch ( lc->cmd ) {
			case LC_SYMTAB:
				stc = (struct symtab_command *) lc;
				break;
				
			case LC_SEGMENT: {
				++segmentIndex;
				struct segment_command *segc = (struct segment_command *) lc; 
				tracerDebugMachO("segment32: %d = %-16.16s @ 0x%08x", segmentIndex, segc->segname, segc->vmaddr);
				if( 0 == strncmp(segc->segname, SEG_PAGEZERO, sizeof(segc->segname) ) ) {
					pageZeroSegmentIndex = segmentIndex;
				} else if( 0 == strncmp(segc->segname, SEG_TEXT, sizeof(segc->segname) ) ) {
					textSegmentIndex = segmentIndex;
				}
				
				break;
			}
				
			case LC_SEGMENT_64: {
				++segmentIndex;
				struct segment_command_64 *segc = (struct segment_command_64 *) lc; 
				tracerDebugMachO("segment64: %d = %-16.16s @ 0x%016llx", segmentIndex, segc->segname, segc->vmaddr);
				if( 0 == strncmp(segc->segname, SEG_PAGEZERO, sizeof(segc->segname) ) ) {
					pageZeroSegmentIndex = segmentIndex;
				} else if( 0 == strncmp(segc->segname, SEG_TEXT, sizeof(segc->segname) ) ) {
					textSegmentIndex = segmentIndex;
				}
				break;
			}
		} /* switch lc_cmd */
	} /* for lc */
	
	if( NULL != stc ) {
		tracerDebugMachO("LC_SYMTAB: symoff: 0x%08x nsyms: %u stroff: 0x%08x strsize: %u", 
						 stc->symoff, stc->nsyms, stc->stroff, stc->strsize);
	} else {
		tracerDebugMachO("HAVE NO LC_SYMTAB !!!");
		ret = TRACER_FAILURE;
	}
	
	UTIL_NLIST *sym = (UTIL_NLIST *) ((char *) mhp + stc->symoff);
	
	const char *strtab = (char *) mhp + stc->stroff;
	
	tracerDebugSym("sym: %p str: %p", (void*)sym, (void*)strtab);
	
	unsigned int symIdx;
	
	unsigned int symUsed = 0;
	for( symIdx = 0 ; ret == TRACER_SUCCESS && symIdx < stc->nsyms ; ++sym, ++symIdx ) {
		
		/* protect against run-away entries - and respect an ancient rule of n_strx == 0 -> name is "" */
		uint32_t strx = sym->n_un.n_strx;
		const char *name = strx ? ( strx < (unsigned int)stc->strsize ? strtab + strx : NULL) : "";
		uint8_t maskedType = sym->n_type & N_TYPE;
		
#ifdef TRACER_DEBUG_LIMIT
		if( NULL != name && *name && strstr(TRACER_DEBUG_LIMIT, name) ) 
#endif
			tracerDebugSymHeavy(
#ifdef __LP64__
								"\tSYMRAW: %5d: 0x%016llx T0x%02x S%02d %.255s", 
#else
								"\tSYMRAW: %5d: 0x%08llx T0x%02x S%02d %.255s", 
#endif
								symIdx, (unsigned long long) sym->n_value, sym->n_type, sym->n_sect, name ? name : "***BAD***");
		
		if( 0 != (sym->n_type & N_STAB ) ) /* stabs for debugger */
			continue;
		
		if( ! (
			   ( maskedType == N_ABS && (sym->n_type & N_EXT) ) /* absolute extern, for _mh_execute_header */ 
			   ||
			   maskedType == N_SECT /* symbol defined here */
			   ) ) 
			continue;
		
		/* skip lots of stuff - maybe too much */
		if( sym->n_sect != pageZeroSegmentIndex && sym->n_sect != textSegmentIndex && !( maskedType == N_ABS && sym->n_sect == NO_SECT ) )
			continue;
		
		if( NULL != name ) {
			if( 0 != strcmp(name, "start") ) {
				if( '_' != *name ) /* skip non underscored symbols - mostly useless */
					continue;
				else
					++name; /* make the rest more familiar (and demangle-able) */
			}
		} else {
			name = "???";
		}	
		
		if( ( '-' == *name || '+' == *name ) && '[' == name[1] ) /* skip objc symbols - they are dynamic anyway */
			continue;
		
#ifdef TRACER_DEBUG_LIMIT
		if( strstr(TRACER_DEBUG_LIMIT, name) ) 
#endif
			tracerDebugSymHeavy("\tCOOKED: %5d: %.80s", symIdx, name);
		
		++symUsed;
		
		uintptr_t liveValue = sym->n_value + ( ( sym->n_sect == pageZeroSegmentIndex || maskedType == N_ABS ) ? 0 : (uintptr_t) live_mhp );
		
		ret = (*symbolAction)(imagePath, name, liveValue, symbolActionInfo, options);
		
	} /* for symbols */
	
	tracerDebugSym("used %u of %u symbols - ret: %d", symUsed, stc->nsyms, ret);
	
	return ret;
}

int UTIL_NO_INSTRUMENT
tracerWalkSymbolTables( TRACER_SYMBOL_WORKER symbolAction, void *symbolActionInfo, uint64_t options )
{
    uint32_t i, numImages;
    const char *imagePath;
    
    int ret = TRACER_SUCCESS;
    
    numImages = _dyld_image_count();
	
    for( i = 0 ; i < numImages ; ++i ) {
        imagePath = _dyld_get_image_name( i );
		
        intptr_t slide = _dyld_get_image_vmaddr_slide( i );
		
		const UTIL_MACH_HEADER *mhp = (const UTIL_MACH_HEADER *) _dyld_get_image_header( i );
		
		ret = tracerAnalyzeFile(mhp, imagePath, slide, symbolAction, symbolActionInfo, options);
		
		tracerDebugMachO("Image %d: %s mh %p slide: %p ret: %d ", i, imagePath, (void*)mhp, (void*)slide, ret);
    }
	
    return ret;
}    


int UTIL_NO_INSTRUMENT 
tracerSymbolStoreCollector(const char *imagePath, const char *name, uint64_t value, void *info, uint64_t options)
{
	TRACER_SYMBOL_STORE *store = info;
	
	TRACER_STORE_OR_RETURN(store, TRACER_FAILURE);
	
	int imagePathExtraLen = -1;
	
	if( NULL != imagePath ) {
		if( imagePath != store->current_imagePath ) {
			imagePathExtraLen = (int) strlen(imagePath);
		}
	} else {
		store->current_strtab_imageName_index = 0;
		store->current_strtab_imagePath_index = 0;
	}
	
	int namelen = (int) strlen(name);
	while( store->strtab_capacity < store->strtab_size + namelen + 1 + imagePathExtraLen + 1) {
		uint32_t new_capacity = store->strtab_capacity + store->strtab_capacity_growth;
		store->strtab = realloc( (void *) store->strtab, new_capacity );
		if( NULL == store->strtab ) {
			tracerReturnWithMessage(TRACER_FAILURE, "out of memory for strtab_capacity = %lu", (unsigned long) new_capacity);
		} else {
			store->strtab_capacity = new_capacity; 
			tracerDebugStore("new strtab_capacity = %lu", (unsigned long) store->strtab_capacity);
		}
		
		if( store->strtab_size == 0 ) {
			*((char*) store->strtab) = 0; /* empty entry at index 0 (historic convention, adopted here) */
			store->strtab_size = 1;
		}
	}
	
	while( store->symbols_capacity < store->symbols_size + 1) {
		uint32_t new_capacity = store->symbols_capacity + store->symbols_capacity_growth;
		store->symbols = realloc( store->symbols, new_capacity * sizeof( TRACER_SYMBOL ) );
		if( NULL == store->symbols ) {
			tracerReturnWithMessage(TRACER_FAILURE, "out of memory for symbols_capacity = %lu", (unsigned long) new_capacity);
		} else {
			store->symbols_capacity = new_capacity; 
			tracerDebugStore("new symbols_capacity = %lu", (unsigned long) store->symbols_capacity);
		}
	}
	
	uint32_t nameIndex = store->strtab_size;
	strcpy((char*) store->strtab + store->strtab_size, name );
	store->strtab_size += namelen + 1;
	
	TRACER_SYMBOL *symbol = &store->symbols[store->symbols_size++];
	
	if( imagePathExtraLen != -1 ) {
		char *imagePathCopy = (char *) store->strtab + store->strtab_size;
		store->current_strtab_imagePath_index = store->strtab_size;
		strcpy(imagePathCopy, imagePath );
		store->strtab_size += imagePathExtraLen + 1;
		
		char *startOfName = strrchr(imagePathCopy, UTIL_PATH_SEPARATOR);
		if( NULL == startOfName )
			startOfName = imagePathCopy;
		
		store->current_strtab_imageName_index = store->current_strtab_imagePath_index + (uint32_t)((startOfName + 1) - imagePathCopy);
	}
	
	symbol->strtab_index = nameIndex;
	symbol->value = value;
	symbol->strtab_imagePath_index = store->current_strtab_imagePath_index;
	symbol->strtab_imageName_index = store->current_strtab_imageName_index;
	
#ifdef TRACER_DEBUG_LIMIT
	if( strstr(TRACER_DEBUG_LIMIT, store->strtab + symbol->strtab_index) ) 
#endif
		tracerDebugSym("%s %s = 0x%llx", 
					   store->strtab + symbol->strtab_imageName_index, 
					   store->strtab + symbol->strtab_index, 
					   (unsigned long long) symbol->value
					   );
	
	return TRACER_SUCCESS;
}

int UTIL_NO_INSTRUMENT
tracerSymbolStoreInit(TRACER_SYMBOL_STORE *store)
{
	TRACER_STORE_OR_RETURN(store, TRACER_FAILURE);
	
	store->symbols = NULL;
	store->symbols_size = 0;
	store->symbols_capacity = 0;
	store->symbols_capacity_growth = 50 * 1000;
	
	store->strtab = NULL;
	store->strtab_size = 0;
	store->strtab_capacity = 0;
	store->strtab_capacity_growth = 1024 * 1024;
	
	/* internal */
	store->current_imagePath = NULL;
	store->current_strtab_imagePath_index = 0;
	store->current_strtab_imageName_index = 0;
	
	return TRACER_SUCCESS;
}

uint32_t UTIL_NO_INSTRUMENT
tracerSymbolStoreCount( TRACER_SYMBOL_STORE *store )
{
	TRACER_STORE_OR_RETURN(store, 0);
	
	return store->symbols_size;
}

const char * UTIL_NO_INSTRUMENT
tracerSymbolStoreNameOfSymbol( TRACER_SYMBOL_STORE *store, TRACER_SYMBOL *symbol ) {
	TRACER_STORE_OR_RETURN(store, 0);
	return store->strtab + symbol->strtab_index;
}

const char *UTIL_NO_INSTRUMENT
tracerSymbolStoreImageNameOfSymbol( TRACER_SYMBOL_STORE *store, TRACER_SYMBOL *symbol ) {
	TRACER_STORE_OR_RETURN(store, 0);
	return store->strtab + symbol->strtab_imageName_index;
}

const char * UTIL_NO_INSTRUMENT
tracerSymbolStoreImagePathOfSymbol( TRACER_SYMBOL_STORE *store, TRACER_SYMBOL *symbol ) {
	TRACER_STORE_OR_RETURN(store, 0);
	return store->strtab + symbol->strtab_imagePath_index;
}

int UTIL_NO_INSTRUMENT
tracerSymbolStoreShow( TRACER_SYMBOL_STORE *store )
{
	TRACER_STORE_OR_RETURN(store, TRACER_FAILURE);
	
	tracerMessage( "store: %p symbols: %lu (cap %lu) mem: symcap %luk + strcap %luk = %luk",
				  (void*)store,
				  (unsigned long int)store->symbols_size,
				  (unsigned long int)store->symbols_capacity,
				  (unsigned long int)store->symbols_capacity * sizeof(*store->symbols) / 1024UL,
				  (unsigned long int)store->strtab_capacity / 1024UL,
				  ((unsigned long int)store->strtab_size + (unsigned long int)store->symbols_capacity * sizeof(*store->symbols)) / 1024UL);
	
	return TRACER_SUCCESS;
}

int UTIL_NO_INSTRUMENT
tracerSymbolStoreShowSymbol( TRACER_SYMBOL_STORE *store, TRACER_SYMBOL *symbol, uint64_t offset )
{  
	TRACER_STORE_OR_RETURN(store, TRACER_FAILURE);
	
	tracerMessage(
#ifdef __LP64__
				  "0x%016llx %-30.30s %.255s + %llu",
#else
				  "0x%08llx %-30.30s %.255s + %llu", 
#endif
				  ( symbol ? (unsigned long long) symbol->value : 0ULL) + offset, 
				  symbol ? store->strtab + symbol->strtab_imageName_index : "???", 
				  symbol ? store->strtab + symbol->strtab_index : "0x0",
				  offset
				  );
	
	return TRACER_SUCCESS;
}

int UTIL_NO_INSTRUMENT
tracerSymbolStoreShowContents( TRACER_SYMBOL_STORE *store )
{
	TRACER_STORE_OR_RETURN(store, TRACER_FAILURE);
	
	uint32_t i, count = tracerSymbolStoreCount( store );
	int ret;
	
	for( i = 0 ; i < count ; ++i ) {
		ret = tracerSymbolStoreShowSymbol( store, &store->symbols[i], 0 );
		if( TRACER_SUCCESS != ret ) 
			return ret;
	}
	
	return TRACER_SUCCESS;
}



int UTIL_NO_INSTRUMENT
tracerSymbolStoreSorterByAddress( void *sorterInfo /*__attribute__((used))*/, const TRACER_SYMBOL *a, const TRACER_SYMBOL *b )
{
	return ( a->value < b->value ) ? -1 : ( a->value == b->value ) ? 0 : 1;
}

int UTIL_NO_INSTRUMENT
tracerSymbolStoreSort( TRACER_SYMBOL_STORE *store, TRACER_SYMBOL_SORTER sorter, void *sorterInfo )
{
	TRACER_STORE_OR_RETURN(store, TRACER_FAILURE);
	
	if( NULL != store->symbols )
		qsort_r(store->symbols, store->symbols_size, sizeof(*store->symbols), sorterInfo, 
				(int (*)(void *, const void *, const void *)) sorter);
	
	return TRACER_SUCCESS;
}



TRACER_SYMBOL_STORE * UTIL_NO_INSTRUMENT
tracerSymbolStoreAllocate(void)
{
	TRACER_SYMBOL_STORE *store = malloc( sizeof(TRACER_SYMBOL_STORE) );
	
	if( NULL == store )
		tracerReturnWithMessage(NULL, "could not allocate tracerSymbolStore - failing");
	
	if( TRACER_SUCCESS != tracerSymbolStoreInit( store ) ) {
		tracerSymbolStoreRelease(store);
		tracerReturnWithMessage(NULL, "could not initialize tracerSymbolStore - failing");
	}
	
	tracerDebugStore("new store %p", (void*)store);
	
	return store;
}

void UTIL_NO_INSTRUMENT
tracerSymbolStoreRelease( TRACER_SYMBOL_STORE *store )
{
	TRACER_STORE_OR_RETURN(store, /**/);
	
#if TRACER_DEBUG_STORE
	tracerSymbolStoreShow(store);
#endif
	
	tracerDebugStore("free store %p", (void*)store);
	
	if( NULL == store )
		tracerReturnWithMessage(/**/, "trying to release NULL store");
	
	if( store->symbols )
		free( store->symbols );
	if( store->strtab )
		free( (void *) store->strtab );
	
	free( store );
}

TRACER_SYMBOL_STORE * UTIL_NO_INSTRUMENT
tracerSymbolStoreCollect(uint64_t options, TRACER_SYMBOL_SORTER sorter, void *sorterInfo)
{
	TRACER_SYMBOL_STORE *store = tracerSymbolStoreAllocate();
	
	if( TRACER_SUCCESS != tracerWalkSymbolTables(tracerSymbolStoreCollector, store, options) ) {
		tracerSymbolStoreRelease(store);
		tracerReturnWithMessage(NULL, "failure walking symbol tables");
	}
	
	if( NULL != sorter ) {
		if( TRACER_SUCCESS != tracerSymbolStoreSort(store, sorter, sorterInfo ) ) {
			tracerSymbolStoreRelease(store);
			tracerReturnWithMessage(NULL, "could not sort store");
		}
	}
	
	return store;
}

TRACER_SYMBOL_STORE * UTIL_NO_INSTRUMENT
tracerSymbolStoreForLookupByAddress(void)
{
	return tracerSymbolStoreCollect(TRACER_OPT_DEFAULT, tracerSymbolStoreSorterByAddress, NULL);
}


int UTIL_NO_INSTRUMENT
tracerSymbolStoreLookupByAddress( TRACER_SYMBOL_STORE *store, uint64_t address, TRACER_SYMBOL **symbolPtr, uint64_t *offsetPtr )
{
	/* we don't use bsearch here because it returns hit or nothing - and this is fast enough */
	
	if( symbolPtr )
		*symbolPtr = NULL;
	
	if( offsetPtr )
		*offsetPtr = 0;
	
	TRACER_STORE_OR_RETURN(store, TRACER_FAILURE);
	
	uint32_t i = 0 , count = tracerSymbolStoreCount( store );
	
	while( i < count && store->symbols[i].value < address )
		++i;
	
	if( 0 == i ) { /* address is before first symbol */
		tracerDebugLookup("address (0x%llx) < first symbol (0x%llx) - returning NULL", 
						  (unsigned long long) address, (unsigned long long) store->symbols[i].value);
		return TRACER_FAILURE;
	} else {
		if( store->symbols[i].value != address ) 
			--i; /* positive offset to previous symbol */
	}
	
	TRACER_SYMBOL *sym = &store->symbols[i];
	
	uint64_t offset = address - sym->value;
	
	if( symbolPtr )
		*symbolPtr = sym;
	
	if( offsetPtr )
		*offsetPtr = offset;
	
	return TRACER_SUCCESS;
}

void UTIL_NO_INSTRUMENT
_tracerDump(int skipframes, void **pcs, int frames)
{
	int i;

	if( backtrace_symbols ) {
		char **strs = backtrace_symbols(pcs, frames);

		for (i = skipframes ; i < frames; ++i) {
			if( pcs[i] > (void *) 0x10 ) { /* bug in os x as of 10.5.2 - argc shows up as the lowest frame if 1..3 - mostly 64bit */
				printf("%s\n", strs[i]);
			}
		}

		free(strs);
	}
	
	TRACER_SYMBOL_STORE *store = tracerSymbolStoreForLookupByAddress();
	
	if( NULL == store ) 
		return;
	
	TRACER_SYMBOL *symbol = NULL;
	uint64_t offset = 0;
	
	for(i = skipframes ; i < frames ; ++i) {
		if( pcs[i] > (void *) 0x8 ) { /* bug in os x as of 10.5.2 - argc shows up as the lowest frame if 1..3 - mostly 64bit */
			if( TRACER_SUCCESS == tracerSymbolStoreLookupByAddress( store, (uint64_t) (uintptr_t) pcs[i], &symbol, &offset ) ) {
				tracerSymbolStoreShowSymbol(store, symbol, offset);
			} else {
				tracerSymbolStoreShowSymbol(store, NULL, (uintptr_t) pcs[i]);
			}
		}
	}

	tracerSymbolStoreRelease(store);
}

#endif
/* __APPLE__ */

#ifdef __GNUC__

/* not thread safe */

static int isTracing = 0;
static char *traceFile = "/tmp/traceFile.trc";
static char *dumpFile = "/tmp/dumpFile.txt";
static int tracerFileHandle = -1;

void __attribute__((__no_instrument_function__))
tracerBeginInstrumentation(void)
{
	if( isTracing ) {
		fprintf(stderr, "%s: tracing is already active - ignoring\n", __UTIL_PRETTY_FUNCTION__);
		return;
	}
	
	tracerFileHandle = open(traceFile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	
	if( tracerFileHandle >= 0 ) {
		tracerInstrumentationEvent((int)TRACER_EVENT_TYPE_BEGIN, (void*) TRACER_EVENT_VERSION, (void*) sizeof(TRACER_EVENT));
		isTracing = 1;
	} else {
		fprintf(stderr, "%s: could not create trace file '%s' (%s) - aborting\n", __UTIL_PRETTY_FUNCTION__, traceFile, strerror(errno));
		tracerFileHandle = -1;
	}
}

void __attribute__((__no_instrument_function__))
tracerEndInstrumentation(void)
{
	FILE *dumpFP = NULL;
	
	if( isTracing ) {
		isTracing = 0;
		tracerInstrumentationEvent((int)TRACER_EVENT_TYPE_END, NULL, NULL);
	}
	
	if(tracerFileHandle >= 0) {
		
		TRACER_SYMBOL_STORE *store = tracerSymbolStoreForLookupByAddress();
		
		if( NULL == store ) {
			fprintf(stderr, "%s: could not create symbol store - returning early\n", __UTIL_PRETTY_FUNCTION__);
			return;
		}
		
		fprintf(stderr, "%s: writing dump to %s\n", __UTIL_PRETTY_FUNCTION__, dumpFile);
		
		dumpFP = fopen(dumpFile, "w");
		
		if( NULL == dumpFP ) {
			fprintf(stderr, "%s: could not create dumpFile '%s' (%s) - returning early\n", __UTIL_PRETTY_FUNCTION__, dumpFile, strerror(errno));
			return;
		}
		
#ifdef __OBJC__
		NSMutableDictionary *lookupCache = [[NSMutableDictionary alloc] init];
		
		TRACER_RUNTIME_SCANNER_INFO info;
		tracerRuntimeScannerInfoInit(&info);
		
		info.symbolStore = store;
#endif
		
		lseek(tracerFileHandle, 0, SEEK_SET);
		
		TRACER_EVENT event;
		int depth = 0;
		
		while( sizeof(TRACER_EVENT) == read(tracerFileHandle, &event, sizeof(TRACER_EVENT) ) ) {
#ifndef __OBJC__
			TRACER_SYMBOL *symbol = NULL;
			TRACER_SYMBOL *callerSymbol = NULL;
			const char *symbolName = NULL;
			const char *callerName = NULL;
			uint64_t offset = 0;
			uint64_t callerOffset = 0;
#endif
			
			if( event.function == _OSSwapInt32 ) // workaround for heavy testing display (inlined)
				continue;
			
			int enter = ( event.eventType == TRACER_EVENT_TYPE_ENTER );
			int swap = 0;
			
			switch( event.eventType ) {
				case TRACER_EVENT_TYPE_ENTER:
				case TRACER_EVENT_TYPE_EXIT:
					
					if( ! enter ) 
						--depth;
					
#ifdef __OBJC__
					NSNumber *functionAddress = [NSNumber numberWithUnsignedLongLong: UTIL_PTR_AS_ULL( event.function ) ];
					NSNumber *callerAddress = [NSNumber numberWithUnsignedLongLong: UTIL_PTR_AS_ULL( event.call_site ) ];
					NSDictionary *frameInfo = [lookupCache objectForKey: functionAddress];
					NSDictionary *callerFrameInfo = [lookupCache objectForKey: callerAddress];
					
					if( nil == frameInfo ) {
						frameInfo = tracerFrameInfoForAddress( UTIL_PTR_AS_ULL( event.function ), &info);
						[lookupCache setObject: frameInfo forKey: functionAddress];
					}
					
					if( nil == callerFrameInfo ) {
						callerFrameInfo = tracerFrameInfoForAddress( UTIL_PTR_AS_ULL( event.call_site ), &info);
						[lookupCache setObject: callerFrameInfo forKey: callerAddress];
					}
					
					fprintf(dumpFP, "%*s %p %s+%llu ( %p %s+%llu )\n", depth+1, enter ? ">" : "<", 
							swap ? event.call_site : event.function,
							[[swap ? callerFrameInfo : frameInfo valueForKey: kTracerSymbolName] UTF8String],
							[[swap ? callerFrameInfo : frameInfo valueForKey: kTracerSymbolOffset] unsignedLongLongValue],
							!swap ? event.call_site : event.function,
							[[!swap ? callerFrameInfo : frameInfo valueForKey: kTracerSymbolName] UTF8String],
							[[!swap ? callerFrameInfo : frameInfo valueForKey: kTracerSymbolOffset] unsignedLongLongValue]
							);
					
#else
					if( TRACER_SUCCESS == tracerSymbolStoreLookupByAddress( store, UTIL_PTR_AS_ULL( event.function ), &symbol, &offset ) ) {
						symbolName = tracerSymbolStoreNameOfSymbol( store, symbol );
					}
					
					if( TRACER_SUCCESS == tracerSymbolStoreLookupByAddress( store, UTIL_PTR_AS_ULL( event.call_site ), &callerSymbol, &callerOffset ) ) {
						callerName = tracerSymbolStoreNameOfSymbol( store, callerSymbol );
					}
					
					fprintf(dumpFP, "%*s %p %s+%llu ( %p %s+%llu )\n", depth+1, enter ? ">" : "<", 
							swap ? event.call_site : event.function, 
							swap ? callerName : symbolName,
							swap ? callerOffset : offset,
							!swap ? event.call_site : event.function, 
							!swap ? callerName : symbolName,
							!swap ? callerOffset : offset
							);
					
#endif
					
					if( enter ) 
						++depth;
					
					break;
			}
			
		} /* while events */
		
		close(tracerFileHandle);
		
		tracerSymbolStoreRelease(store);
		
		fclose(dumpFP);
		
		fprintf(stderr, "%s: finished writing dump to %s\n", __UTIL_PRETTY_FUNCTION__, dumpFile);
	}
	
}

void __attribute__((__no_instrument_function__))
tracerInstrumentationEvent(unsigned long eventType, void *this_fn, void *call_site)
{
	static int didReport = 0;
	
	TRACER_EVENT event = { eventType, this_fn, call_site, pthread_self() };
	
	if( sizeof(TRACER_EVENT) != write(tracerFileHandle, &event, sizeof(TRACER_EVENT)) ) {
		if( 0 == didReport ) {
			didReport = 1;
			fprintf(stderr, "%s: could not write to trace file %s (%s) - disabling\n",  __UTIL_PRETTY_FUNCTION__, traceFile, strerror(errno));
			isTracing = 0;
			close(tracerFileHandle);
			tracerFileHandle = -1;
		}
	}
	
}

void __attribute__((__no_instrument_function__))
__cyg_profile_func_enter(void *this_fn, void *call_site)
{
	if( isTracing ) 
		tracerInstrumentationEvent(TRACER_EVENT_TYPE_ENTER, this_fn, call_site);
}

void __attribute__((__no_instrument_function__))
__cyg_profile_func_exit(void *this_fn, void *call_site)
{
	if( isTracing ) 
		tracerInstrumentationEvent(TRACER_EVENT_TYPE_EXIT, this_fn, call_site);
}
#else
void tracerStartInstrumentation(void) { fprintf(stderr, "%s not implemented\n", __UTIL_PRETTY_FUNCTION__); }
void tracerStopInstrumentation(void)  { fprintf(stderr, "%s not implemented\n", __UTIL_PRETTY_FUNCTION__); }
#endif
/* __GNUC__ for instrumentation */

#ifdef TRACER_TEST

int tracerTracer( void *sorterInfo /*__attribute__((used))*/, const TRACER_SYMBOL *a, const TRACER_SYMBOL *b )
{
	tracerDump();
	return ( a->value < b->value ) ? -1 : ( a->value == b->value ) ? 0 : 1;
}

int tracerCTest(int argc, const char **argv)
{
	int argIndex = 1;
	int verbose = 0;
	
	if( NULL != argv[argIndex] && 0 == strncmp(argv[argIndex], "-v", 2) ) {
		verbose = strlen(argv[argIndex]) - 1; /* allow -vv */
		++argIndex;
	}
	
	util_watch_start(collection);
	
	TRACER_SYMBOL_STORE *store = tracerSymbolStoreForLookupByAddress();
	
	if( NULL == store ) 
		tracerReturnWithMessage(1, "could not allocate symbol store");
	
	if( verbose >= 1 ) {
		tracerMessage("collection took %.3fs", util_watch_seconds(collection));
		tracerSymbolStoreShow( store );
		
		if( verbose >= 2 )
			tracerSymbolStoreShowContents( store );
	}
	
	TRACER_SYMBOL *symbol = NULL;
	uint64_t offset = 0;
	
	int main(int argc, const char **argv);
	if( TRACER_SUCCESS == tracerSymbolStoreLookupByAddress( store, (uint64_t) main + 23, &symbol, &offset ) ) {
		tracerSymbolStoreShowSymbol(store, symbol, offset);
	} else {
		tracerMessage("main not found");
	}
	
	if( TRACER_SUCCESS == tracerSymbolStoreLookupByAddress( store, (uint64_t) printf + 42, &symbol, &offset ) ) {
		tracerSymbolStoreShowSymbol(store, symbol, offset);
	} else {
		tracerMessage("printf not found");
	}
	
	if( tracerSymbolStoreCount(store) >= 2 ) {
		qsort_r(store->symbols, 2, sizeof(*store->symbols), (void *) store, 
				(int (*)(void *, const void *, const void *)) tracerTracer);
	}
	
	tracerSymbolStoreRelease( store );
	
	return 0;
}

#ifndef __OBJC__
int main(int argc, const char **argv)
{
	int ret;
	
	tracerBeginInstrumentation();
	
	ret = tracerCTest(argc, argv);
	
	tracerEndInstrumentation();
	
	return ret;
}
#endif
/* __OBJC__ */

#endif
/* TRACER_TEST */


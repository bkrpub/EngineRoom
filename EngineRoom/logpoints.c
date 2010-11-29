/*
 This file is part of EngineRoom, Copyright (c) 2007-2010 Bjoern Kriews, Hamburg - All rights reserved.

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

 Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer
 in the documentation and/or other materials provided with the distribution.

 Neither the name of the author nor the names of its contributors may be used to endorse or promote products derived from this
 software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#define __LOGPOINTS_C__ 1

//#define SELF_TRACE(fmt, ...) fprintf(stderr, "TRC: "##fmt##"\n", __VA_ARGS__) 
#define SELF_TRACE(fmt, ...) /**/

#include "logpoints_api.h"

#include "er_compat.h"

#ifdef __APPLE_CC__
#pragma mark Getting and setting LogPoint handlers
#endif

/* private - may be replaced by thread-local stuff */
static LOGPOINT_INVOKER  _logPointInvoker  = logPointInvokerDefault;
static LOGPOINT_COMPOSER _logPointComposer = logPointComposerDefault;
static LOGPOINT_EMITTER  _logPointEmitter  = logPointEmitterDefault;

LOGPOINT_INVOKER logPointGetInvoker(void) 
{ 
  return _logPointInvoker;
}

LOGPOINT_INVOKER logPointSetInvoker(LOGPOINT_INVOKER newInvoker) 
{ 
  LOGPOINT_INVOKER previousInvoker = _logPointInvoker;
  _logPointInvoker = newInvoker ? newInvoker : logPointInvokerDefault;
  return previousInvoker;
}

LOGPOINT_COMPOSER logPointGetComposer(void)
{
  return _logPointComposer;
}

LOGPOINT_COMPOSER logPointSetComposer(LOGPOINT_COMPOSER newComposer)
{
  LOGPOINT_COMPOSER previousComposer = _logPointComposer;
  _logPointComposer = newComposer ? newComposer : logPointComposerDefault;
  return previousComposer;
}

LOGPOINT_EMITTER logPointGetEmitter(void)
{
  return _logPointEmitter;
}

LOGPOINT_EMITTER logPointSetEmitter(LOGPOINT_EMITTER newEmitter)
{
  LOGPOINT_EMITTER previousEmitter = _logPointEmitter;
  _logPointEmitter = newEmitter ? newEmitter : logPointEmitterDefault;
  return previousEmitter;
}

LOGPOINT_INVOKER_DECLARATION(logPointInvokerDefault)
{
  lp_return_t ret = LOGPOINT_YES;
SELF_TRACE("invoker1");
  void *msg = NULL;

  if( ! LOGPOINT_IS_SILENT( *lpp ) ) {

    if( NULL != fmt ) {
      va_list args;
      va_start(args, fmt); 
      
#ifdef __OBJC__
      CFStringRef cfFmt = NULL;
      
      if( NO == LOGPOINT_IS_NSSTRING(*lpp) ) {
SELF_TRACE("invoker2");
	cfFmt = CFStringCreateWithCStringNoCopy(kCFAllocatorDefault, (const char *) fmt, kCFStringEncodingUTF8, kCFAllocatorNull /* don't free */);
      } else {
 SELF_TRACE("invoker3");
	cfFmt = (CFStringRef) fmt;
      }
      
      msg = (void *) CFStringCreateWithFormatAndArguments(kCFAllocatorDefault, NULL /* fmtOptions */, cfFmt, args);
SELF_TRACE("invoker4");
#else
      util_vasprintf((char **) &msg, fmt, args);
#endif
//SELF_TRACE("invoker5 comp = %p\n", logPointGetComposer());      
      ret = (*logPointGetComposer())(lpp, langspec1, langspec2, msg);
SELF_TRACE("invoker6");      
#ifdef __OBJC__
      if( NULL != cfFmt )
	CFRelease( cfFmt );
#endif
      
      va_end(args);
    } else {
SELF_TRACE("invoker7 comp = %p\n", logPointGetComposer());      
      ret = (*logPointGetComposer())(lpp, langspec1, langspec2, NULL);
SELF_TRACE("invoker8");      
    } /* fmt != NULL */

  } /* ! SILENT */


  if( LOGPOINT_IS_ASSERT(*lpp) ) {
#if DEPRECATED_ASSERTION_HANDLING
#ifdef __OBJC__    
    if( LOGPOINT_IS_OBJC(*lpp) ) {
      [[NSAssertionHandler currentHandler] handleFailureInMethod: (SEL)langspec2 object: (id)langspec1 file: [NSString stringWithUTF8String: lpp->file] lineNumber: (int) lpp->line description: @"%@", msg];
    } else {
      [[NSAssertionHandler currentHandler] handleFailureInFunction: [NSString stringWithUTF8String: lpp->function] file: [NSString stringWithUTF8String: lpp->file] lineNumber: (int)lpp->line description: @"%@", msg];
    }
    fprintf(stderr, "Unexpected return from assertion handler\n");
    abort();
#else
    abort();
#endif
#endif
  }
SELF_TRACE("invoker9");      
#if MAINTAINER_WARNINGS
#warning this will leak for assertion exceptions which are catched
#endif
#ifdef __OBJC__
  if( NULL != msg ) 
    CFRelease( (CFStringRef) msg);
#else
  free( msg );
#endif

SELF_TRACE("invoker10");      

  return ret;
}

static int logPointShowInstanceInfo UTIL_UNUSED = 1;
LOGPOINT_COMPOSER_DECLARATION(logPointComposerDefault)
{
#if MAINTAINER_WARNINGS
#warning no nssstringmode for keys and label yet
#endif
  const char *kind = (kLogPointKindNone == lpp->kind) ? "" : lpp->kind;
  const char *keys = (kLogPointKeysNone == lpp->keys) ? "" : lpp->keys;
  const char *label = (kLogPointLabelNone == lpp->label) ? "" : lpp->label;
#ifdef __OBJC__
  const char *methodName = NULL;
  const char *className = NULL;
  char *instanceInfo = NULL;
  BOOL isClassMethod = NO;
SELF_TRACE("composer1");      
  if( LOGPOINT_IS_OBJC(*lpp) ) {
    id objcSelf = (id) langspec1;	
    SEL objcCmd = (SEL) langspec2; 
SELF_TRACE("composer2 = %p\n", object_getClass);      		
	// using weak symbols
	Class objcClass = COMPAT_OBJECT_GETCLASS(objcSelf);
    isClassMethod = COMPAT_CLASS_ISMETACLASS( objcClass );

SELF_TRACE("composer3 = %p\n", object_getClassName);      		

    className = object_getClassName(objcSelf);

SELF_TRACE("composer4 = %p\n", sel_getName);      		
    methodName = objcCmd ? sel_getName(objcCmd) : lpp->function;
    
    char _instanceInfo[sizeof("0x0123456789abcdef:0123456789")];
    
    if( logPointShowInstanceInfo && NO == isClassMethod ) {
      snprintf(_instanceInfo, sizeof(_instanceInfo), "%p:%u", (void*)objcSelf, (unsigned int) [objcSelf retainCount]);
      _instanceInfo[ sizeof(_instanceInfo) - 1] = 0;
      instanceInfo = _instanceInfo;
    }
  }
SELF_TRACE("composer5");      		  
#endif
SELF_TRACE("composer6 emit = %p\n", logPointGetEmitter());      		  
  lp_return_t ret = (*logPointGetEmitter())(lpp, langspec1, langspec2, "%s %s%s%s%s:%llu %s%s%s%s%s %s%s%s%s" LOGPOINT_MESSAGE_FORMAT, 
				    kind, 
				    *keys ? "[" : "", keys, *keys ? "] " : "", 
				    logPointFileNameOnly(lpp), (unsigned long long)lpp->line, 
#ifdef __OBJC__
				    className ? (isClassMethod ? "+[" : "-[") : "", 
				    className ? className : "", 
				    className ? " " : "", 
				    methodName ? methodName : lpp->function, 
				    className ? "]" : "",
				    instanceInfo ? instanceInfo : "",
				    instanceInfo ? " " : "",
#else
				    "",
				    "",
				    "",
				    lpp->function,
				    "", 
				    "",
				    "",
#endif
				    label, *label && payload ? " " : "", payload ? payload : LOGPOINT_MESSAGE_EMPTY);

SELF_TRACE("composer7");      		  
  return ret;
}

LOGPOINT_EMITTER_DECLARATION(logPointEmitterDefault)
{
  va_list args;
  va_start(args, fmt);

  lp_return_t ret = LOGPOINT_YES;

#ifdef __OBJC__
  CFStringRef cfFmt = CFStringCreateWithCStringNoCopy(kCFAllocatorDefault, fmt, kCFStringEncodingUTF8, kCFAllocatorNull /* don't free */);  
  NSLogv((NSString*) cfFmt, args);
  CFRelease(cfFmt);
#else
  char *log = NULL;

  int len = util_log_vasprintf(&log, fmt, args);
  if( len+1 != fprintf(stderr, "%s\n", log) )
    ret = LOGPOINT_NO;

  free(log);
#endif

  va_end(args);

  return ret;
}

#ifdef __APPLE_CC__
#pragma mark Private interface
#endif

static LOGPOINT *__logPointListHead = NULL;

LOGPOINT *_logPointListHead(void);

LOGPOINT *_logPointListHead(void)
{
  return __logPointListHead;
}



#ifdef __APPLE_CC__
#pragma mark Functions to be used with logpoints at runtime
#endif

static const char *logPointPriorityNames[] = { "EMERGENCY", "ALERT", "CRITICAL", "ERROR", "WARNING", "NOTICE", "INFO", "DEBUG" };

const char *logPointPriorityNameFromNumber(int priority)
{
  return priority < 0 || priority >= (long) (sizeof(logPointPriorityNames)/sizeof(logPointPriorityNames[0])) ? "BAD_PRIORITY" : logPointPriorityNames[priority];
}

int logPointPriorityNumberFromName(const char *name)
{
  unsigned int i;
  for( i = 0 ; i < sizeof(logPointPriorityNames)/sizeof(logPointPriorityNames[0]) ; ++i ) {
    if( 0 == strcasecmp(name, logPointPriorityNames[i] ) )
      return i;
  }

  return -1;
}

const char *logPointFileNameOnly(LOGPOINT *lpp)
{
  const char *file = strrchr(lpp->file, UTIL_PATH_SEPARATOR);
  
  if( NULL == file || '\0' == file[1] )
    file = lpp->file;
  else
    ++file;

  return file;
}

const char *logPointReturnString(lp_return_t err)
{
  switch(err) {
  case LOGPOINT_RETURN_STOP:
    return "LOGPOINT_RETURN_STOP";

  case LOGPOINT_RETURN_OK:
    return "LOGPOINT_RETURN_OK";
  case LOGPOINT_RETURN_BAD_ALIGNMENT:
    return "LOGPOINT_RETURN_BAD_ALIGNMENT";
  case LOGPOINT_RETURN_BAD_MAGIC:
    return "LOGPOINT_RETURN_BAD_MAGIC";
  case LOGPOINT_RETURN_BAD_SIZE:
    return "LOGPOINT_RETURN_BAD_SIZE";
  case LOGPOINT_RETURN_BAD_STRUCTURE:
    return "LOGPOINT_RETURN_BAD_STRUCTURE";
  case LOGPOINT_RETURN_UNEXPECTED_SIZE:
    return "LOGPOINT_RETURN_UNEXPECTED_SIZE";
  case LOGPOINT_RETURN_NO_IMAGE_LIST:
    return "LOGPOINT_NO_IMAGE_LIST";
  case LOGPOINT_RETURN_NO_IMAGE_NAME:
    return "LOGPOINT_NO_IMAGE_NAME";
  case LOGPOINT_RETURN_BAD_FILTER:
   return "LOGPOINT_RETURN_BAD_FILTER";
  }
  
  return "LOGPOINT_RETURN_UNKNOWN";
}

lp_return_t logPointReset(void) { return logPointDisableSimple(""); }
lp_return_t logPointEnableSimple(const char *filter) { return logPointApplySimple(filter, LOGPOINT_OPTION_ENABLE); }
lp_return_t logPointDisableSimple(const char *filter) { return logPointApplySimple(filter, LOGPOINT_OPTION_DISABLE); }

lp_return_t logPointApplySimple(const char *filter, lp_uint_t options)
{
/*fprintf(stderr, "%s\n", __UTIL_PRETTY_FUNCTION__); */

  if( NULL == filter ) 
    return LOGPOINT_RETURN_OK;

  return logPointApply( logPointFilterSimple /*filter*/, (void*) filter, NULL /*action*/, NULL /*actionInfo*/, options);
}

lp_return_t logPointDumpAll(void)
{
/*fprintf(stderr, "%s\n", __UTIL_PRETTY_FUNCTION__); */

  return logPointApply(NULL /*filter*/, NULL /*filterInfo*/, logPointActionDump /*action*/, NULL /*actionInfo*/, LOGPOINT_OPTION_NONE);
}

lp_return_t logPointActionDump(LOGPOINT *lpp, void *actionInfo UTIL_UNUSED)
{
        const char *keys = lpp->keys ? lpp->keys: "";
	const char *file = logPointFileNameOnly(lpp);

	int formatInfoLen = 1;

	/* remove ", " at EOL from using '#fmt ", " #__VA_ARGS__' with no arguments */
	if( NULL != lpp->formatInfo ) {
	  formatInfoLen = (int) strlen(lpp->formatInfo);
	  if( formatInfoLen > 1 && ',' == lpp->formatInfo[formatInfoLen - 2] && ' ' == lpp->formatInfo[formatInfoLen - 1] )
	    formatInfoLen -= 2;
	}

	fprintf(stderr, "LOGPOINT: %s %s%s%s%s %s:%llu %s %p %s %.*s\n", 
		LOGPOINT_IS_ACTIVE(*lpp) ? "ON " : "OFF", 
		lpp->kind, *keys ? " [" : "", keys, *keys ? "]" : "", 
		file, (unsigned long long)lpp->line, lpp->function, lpp->address, 
		lpp->label ? lpp->label : "-", formatInfoLen, lpp->formatInfo ? lpp->formatInfo : "-");

	return LOGPOINT_RETURN_OK;
}

int logPointFilterSimple(LOGPOINT *lpp, void *filterInfo)
{
	char *filter = filterInfo;
	/*fprintf(stderr, "%s (%s)\n", __UTIL_PRETTY_FUNCTION__, filter); */
	
	if( NULL == filter )
		return LOGPOINT_NO;
	
	size_t filterLen = strlen(filter);
	
	if( 0 == filterLen )
		return LOGPOINT_YES;
	
	char *begin = filter;
	char *end;
	
	do {
		end = strchr(begin, ',');
		
		char *realEnd = end ? end : &filter[filterLen];
		size_t len = realEnd - begin;
		
		if( lpp->keys ) {
			const char *tmp = lpp->keys;
			while(*tmp) {
				if( 0 == strncmp(tmp, begin, len ) ) {
					return LOGPOINT_YES;
				}
				
				++tmp;
			}
		}
		
		begin = realEnd + 1;
		
	} while( end );
	
	
	return LOGPOINT_NO;
}


lp_return_t logPointApplyToData(const char *imageName, LOGPOINT *logpts, size_t logSizeInBytes, 
	LOGPOINT_FILTER filter, void *filterInfo, LOGPOINT_WORKER action, void *actionInfo, lp_uint_t options)
{
/*fprintf(stderr, "%s\n", __UTIL_PRETTY_FUNCTION__); */
    unsigned int brokenLogPoints = 0;
	
    if( sizeof(LOGPOINT) != LOGPOINT_EXPECTED_SIZE ) 
        return LOGPOINT_RETURN_UNEXPECTED_SIZE;
	
    if( ! logpts || ! logSizeInBytes )
        return 0;
    
    size_t nlogs = logSizeInBytes / sizeof(LOGPOINT);
    size_t rest = logSizeInBytes - sizeof(LOGPOINT) * nlogs;
    size_t nread = 0;
    
    if( rest != 0 )
        return LOGPOINT_RETURN_BAD_ALIGNMENT;
	
    if( logpts->magic != LOGPOINT_MAGIC )
        return LOGPOINT_RETURN_BAD_MAGIC;
	
    if( logpts->size != sizeof(LOGPOINT) )
        return LOGPOINT_RETURN_BAD_SIZE;
    
    while( nread != nlogs ) {
		
        if( logpts->magic != LOGPOINT_MAGIC )
            return LOGPOINT_RETURN_BAD_STRUCTURE;
		
		if( ! LOGPOINT_MAGIC_TEST(*logpts) ) {
			return LOGPOINT_RETURN_BAD_MAGIC;
		}
		
		LOGPOINT_SET_DYNAMIC_CODE(*logpts, options & LOGPOINT_OPTION_WALKING_DYNAMIC ? 1 : 0);
        
        logpts->image = imageName;
		
        if( LOGPOINT_IS_BROKEN(*logpts) ) {
            ++brokenLogPoints;
            fprintf(stderr, "logpoints: broken logpoint in %s - %s:%llu",
                    logpts->function, logpts->file, (unsigned long long)logpts->line);
        }
		
        ++nread;
        
	if( 0 == ( options & LOGPOINT_OPTION_IGNORE_HARD ) || ! LOGPOINT_IS_HARD(*logpts) ) {
			
			if( filter == NULL || LOGPOINT_YES == (*filter)(logpts, filterInfo) ) {
				if( options & LOGPOINT_OPTION_DISABLE ) {
				  LOGPOINT_DISABLE(*logpts);
				} else if( options & LOGPOINT_OPTION_ENABLE ) {
				  LOGPOINT_ENABLE(*logpts);
				}

				if( NULL != action ) {
				  if( LOGPOINT_RETURN_STOP == (*action)(logpts, actionInfo ) ) { 
				    break;
				  }
				}
			}
			
		}
        ++logpts;
    }
    
	/* fprintf(stderr, "read %ld entries\n", nread); */
    
    if( brokenLogPoints != 0) {
        fprintf(stderr, "logpoints: detected %u broken logpoint%s, aborting",
                brokenLogPoints, brokenLogPoints > 1 ? "s" : "");
        abort();
    }
    
    return LOGPOINT_RETURN_OK;
}

lp_return_t logPointApply( LOGPOINT_FILTER filter, void *filterInfo, LOGPOINT_WORKER action, void *actionInfo, lp_uint_t options )
{
/*fprintf(stderr, "%s\n", __UTIL_PRETTY_FUNCTION__); */

  lp_return_t ret = logPointPlatformApply(filter, filterInfo, action, actionInfo, options);
  if( LOGPOINT_RETURN_OK != ret ) {
    fprintf(stderr, "logpoints: internal error (%s)\n", logPointReturnString(ret));
  }

  return ret;
}

#ifdef __APPLE__

#import <mach-o/dyld.h>
#import <mach-o/loader.h>
#import <mach-o/arch.h>
#import <mach-o/getsect.h>
#import <mach-o/ldsyms.h>
#import <mach-o/nlist.h>
#import <mach-o/stab.h>
#import <mach-o/fat.h>

lp_return_t logPointPlatformApply( LOGPOINT_FILTER filter, void *filterInfo, LOGPOINT_WORKER action, void *actionInfo, lp_uint_t options )
{
  const char *segname = LOGPOINT_SEGMENT;
  const char *sectname = LOGPOINT_SECTION;
    
    uint32_t i, numImages;
    const char *imageName;
    LOGPOINT *logpts;
    size_t logSizeInBytes;
    
    lp_return_t ret = LOGPOINT_RETURN_OK;
    
    numImages = _dyld_image_count();

    for( i = 0 ; i < numImages ; ++i ) {
        imageName = _dyld_get_image_name( i );
        
        /* skip system stuff, save time */
#if 1
        if( imageName )
            if( imageName == strstr(imageName, "/System") || imageName == strstr(imageName, "/usr") )
                continue;
#else
#warning OPTIMIZATION DISABLED
#endif
        intptr_t slide = _dyld_get_image_vmaddr_slide( i );

        /* this is the recommended method but it does not work from a framework */
	/* int walkingDynamic = ( mhp == &_mh_execute_header ) ? 0 : 1; */

	int walkingDynamic = ( slide == 0 ) ? 0 : 1;

	if( walkingDynamic && (options & LOGPOINT_OPTION_STATIC_ONLY))
	  continue;
	if( ! walkingDynamic && (options & LOGPOINT_OPTION_DYNAMIC_ONLY))
	  continue;

        /* docs say logSizeInBytes is unsigned long, header says uint32_t */
	const UTIL_MACH_HEADER *mhp = (UTIL_MACH_HEADER *) _dyld_get_image_header( i );
#ifdef __LP64__
	uint64_t logSizeTmp;
        logpts = (void *) getsectdatafromheader_64( mhp, segname, sectname, &logSizeTmp );
#else
	uint32_t logSizeTmp;
        logpts = (void *) getsectdatafromheader( mhp, segname, sectname, &logSizeTmp );
#endif

	logSizeInBytes = logSizeTmp;

        if( ! logpts ) /* no such section */
            continue;

        if( walkingDynamic ) 
            logpts = (LOGPOINT *) ((char *) logpts + slide); 

	/* fprintf(stderr, "%d: %s\n\tmh %p dyn: %d slide: %p log: %p siz: %ld\n", i, imageName, mhp, walkingDynamic, slide, logpts, logSizeInBytes); */
                
        ret = logPointApplyToData(imageName, logpts, logSizeInBytes, filter, filterInfo, action, actionInfo, options | (walkingDynamic ? LOGPOINT_OPTION_WALKING_DYNAMIC : 0));
	if( ret != LOGPOINT_RETURN_OK )
	  break;
    }
	
    return ret;
}    



#endif 
/* __APPLE__ */

#ifdef LOGPOINT_USE_ELF

#include <elf.h>
#include <limits.h>

/* for ElfW() cast macro and dl_iterate_phdr on linux */
#include <link.h>

Elf64_Addr getSectionFromELFObject(char *file, char *sectionName, int copy, size_t *lengthPtr);

#ifdef __sun
#if LOGPOINT_64BIT
#define LOGPOINT_ELF_ADDR Elf64_Addr
#else
#define LOGPOINT_ELF_ADDR Elf32_Addr
#endif
#endif

#ifdef __linux__
#define LOGPOINT_ELF_ADDR ElfW(Addr)
#endif


#ifdef __linux__
/* experimental */

struct logPointImageList { 
  int count;
  int capacity;
  const char **images; 
};

static int getImageListCallback(struct dl_phdr_info *info, size_t size, void *data)
{
#if BK_DEBUG
  fprintf(stderr, "getImageList: name='%s' addr=%p\n", info->dlpi_name, (void*) info->dlpi_addr);

  int j;
  for (j = 0; j < info->dlpi_phnum; j++)
                printf("\theader %2d: address=%10p\n", j,
                    (void *) (info->dlpi_addr + info->dlpi_phdr[j].p_vaddr));
#endif
  struct logPointImageList *list = data;

  if( list->capacity == 0 || list->count <= list->capacity - 1 ) {
    list->capacity = list->capacity ? list->capacity * 2 : 256;
    list->images = realloc(list->images, list->capacity * sizeof(const char *));
  }
  
  if( NULL == list->images ) {
    fprintf(stderr, "%s: could not allocate imageList\n", __UTIL_PRETTY_FUNCTION__);
    return 1;
  }
  
  list->images[ list->count ] = info->dlpi_name;

  ++list->count;

  return 0;
}

int getImageList(struct logPointImageList *imageList)
{
  imageList->count = 0;
  imageList->capacity = 0;
  imageList->images = NULL;

    if( 0 != dl_iterate_phdr(getImageListCallback, imageList) || 0 == imageList->count ) {

      if( NULL != imageList->images ) {
	free(imageList->images);
	imageList->images = NULL;
	return LOGPOINT_RETURN_NO_IMAGE_LIST;
      }
    }

    return LOGPOINT_RETURN_OK;
}

#endif
/* __linux__ experimental */

lp_return_t logPointPlatformApply( LOGPOINT_FILTER filter, void *filterInfo, LOGPOINT_WORKER action, void *actionInfo, lp_uint_t options )
{
  lp_return_t ret = LOGPOINT_RETURN_OK;

#ifdef __linux__
  struct logPointImageList imageList;

  ret = getImageList(&imageList);

  if( LOGPOINT_RETURN_OK != ret ) 
    return ret;
#endif

  size_t sectionLength;

#warning fragile method to get path of image    
    char imageName[PATH_MAX+1];
    imageName[0] = '\0';

#if defined( __sun ) || defined( __linux__ ) || defined( __BSD__ ) 

#if defined( __sun )
      char *platformPart = "/path/a.out";
#elif defined( __linux__ )
      char *platformPart = "/exe";
/*#elif defined( __BSD__ ) */
/*char *platformPart = "/file"; */
#endif

    char *linkName = NULL;
    util_asprintf(&linkName, "/proc/%llu%s", (unsigned long long)getpid(), platformPart);
    ssize_t imageNameLen = readlink(linkName, imageName, PATH_MAX);
    free(linkName);

    if( 0 < imageNameLen ) {
      imageName[imageNameLen] = 0;
    } else {
      imageName[0] = '\0';
    }

    if( ! imageName[0] ) {
      fprintf(stderr, "can not determine imageName - no /proc ?");
      return LOGPOINT_RETURN_NO_IMAGE_NAME;
    }
#else
#error no code to determine imageName for this platform
#endif


#warning walking of dynamic libraries not yet implemented
    LOGPOINT *logpts = (LOGPOINT *) (LOGPOINT_ELF_ADDR) getSectionFromELFObject(imageName, LOGPOINT_SECTION, 0, &sectionLength);

    /*fprintf(stderr, "logpts: %p\n", logpts); */

    if( NULL == logpts ) {
      fprintf(stderr, "%s: no logpoints in image\n", imageName);
      return ret;
    }

    ret = logPointApplyToData(imageName, logpts, sectionLength, filter, filterInfo, action, actionInfo, options);

    return ret;
}    

Elf32_Shdr *getELF32SectionHeader(void *mappedImage, const char *sectionName)
{
  Elf32_Ehdr *ehdr = mappedImage;
  unsigned char *image = mappedImage;

  Elf32_Shdr *shdr, *found = NULL;

  const char *sectionNames = (char *) image + ((Elf32_Shdr *) ( image + ehdr->e_shoff + ehdr->e_shstrndx * ehdr->e_shentsize ))->sh_offset;

  Elf32_Half idx;

  for( idx = 0 ; idx < ehdr->e_shnum ; ++idx ) {
    shdr = (Elf32_Shdr *) ( (char *) image + ehdr->e_shoff + idx * ehdr->e_shentsize );

    /*fprintf(stderr, "ELF 32bit Section %02d: %s\n", idx, &sectionNames[ shdr->sh_name ]); */

    if( 0 == strcmp(&sectionNames[ shdr->sh_name ], sectionName ) ) {
      found = shdr;
      break;
    }

  }

  return found;
}

Elf64_Shdr *getELF64SectionHeader(void *mappedImage, const char *sectionName)
{
  Elf64_Ehdr *ehdr = mappedImage;
  unsigned char *image = mappedImage;

  Elf64_Shdr *shdr, *found = NULL;

  const char *sectionNames = (char *) image + ((Elf64_Shdr *) ( image + ehdr->e_shoff + ehdr->e_shstrndx * ehdr->e_shentsize ))->sh_offset;

  Elf32_Half idx;

  for( idx = 0 ; idx < ehdr->e_shnum ; ++idx ) {
    shdr = (Elf64_Shdr *) ( (char *) image + ehdr->e_shoff + idx * ehdr->e_shentsize );

    /* fprintf(stderr, "ELF 64bit Section %02d: %s\n", idx, &sectionNames[ shdr->sh_name ]); */

    if( 0 == strcmp(&sectionNames[ shdr->sh_name ], sectionName ) ) {
      found = shdr;
      break;
    }

  }

  return found;
}


Elf64_Addr getSectionFromELFObject(char *file, char *sectionName, int copy, size_t *lengthPtr)
{
  size_t imageLength;
  void *image = util_map_image(file, &imageLength);

  void *shdr = NULL;

  Elf64_Addr sectionVirtualAddress = 0;
  void *theCopy = NULL;
  void *sectionInImage = NULL;
  size_t sectionLength = 0;

  if( lengthPtr )
    *lengthPtr = 0;

  if( NULL == image )
    utilReturnWithMessage(0, "can not map ELF image from file %s", file);

  if( 0 != strncmp(ELFMAG, image, strlen(ELFMAG)) )
    utilReturnWithMessage(0, "'%s' is not an ELF object", file);

  unsigned char elfClass = ((unsigned char *) image)[EI_CLASS];
 
  switch(elfClass) {
    case ELFCLASS32:
      {
	Elf32_Shdr *shdr32 = getELF32SectionHeader(image, sectionName);
	
	if( NULL != shdr32 ) {
	  shdr = shdr32;
	  sectionLength = (size_t) shdr32->sh_size;
	  sectionInImage = (void *) (image + shdr32->sh_offset);
	  sectionVirtualAddress = shdr32->sh_addr;
	}
      }
      break;
	
    case ELFCLASS64:
      {
	Elf64_Shdr *shdr64 = getELF64SectionHeader(image, sectionName);
	
	if( NULL != shdr64 ) {
	  shdr = shdr64;
	  sectionLength = (size_t) shdr64->sh_size;
	  sectionInImage = (void *) (image + shdr64->sh_offset);
	  sectionVirtualAddress = shdr64->sh_addr;
	}
	
	/* fprintf(stderr, "64bit ELF test info: sectionLength = %llu, image = %p, sectionInImage = %p, virtualAddress = %p\n", (unsigned long long) sectionLength, image, sectionInImage, (void*)sectionVirtualAddress); */
      }
      break;

    default:
      utilReturnWithMessage(0, "ELF object class of '%s' is %d - not supported - see elf.h", file, (int) elfClass);
      break;
  }


  if( NULL != shdr ) {

    if( 0 != copy ) {
      theCopy = malloc(sectionLength);
      
      if( NULL != theCopy ) {
	memcpy(theCopy, sectionInImage, sectionLength);
      }
    }
  }

  util_unmap_image(image, imageLength);

  if( NULL == shdr )
    utilReturnWithMessage(0, "can not locate ELF section '%s' in '%s'", sectionName, file);
 
  if( 0 != copy && NULL == theCopy )
    utilReturnWithMessage(0, "could not allocate memory (%llu bytes) for copy of ELF section '%s' in '%s'", (unsigned long long)sectionLength, sectionName, file);

  if( NULL != lengthPtr ) 
    *lengthPtr = sectionLength;  

  /* this cast allows casting void* to i.e. uint64_t regardless of platform void* width */
  return 0 != copy ? (LOGPOINT_ELF_ADDR) theCopy : sectionVirtualAddress;
}

/* the "elf-test"
main(int argc, char **argv)
{
  size_t length;
  Elf64_Addr section;

  if( NULL == argv[1] ) {
    fprintf(stderr, "Usage: %s <executable-with-logpoint-section>\n", argv[0]);
    return 1;
  }

  section = getSectionFromELFObject(argv[1], ".logpoints", 0, &length);
  
  printf("Virtual Logpoint section is at 0x%llx (%ld bytes)\n", section, length);

  section = getSectionFromELFObject(argv[1], ".logpoints", 1, &length);
  
  printf("Copied  Logpoint section is at 0x%llx (%ld bytes)\n", section, length);

  return 0;
}
*/


#endif
/* LOGPOINTS_USE_ELF */


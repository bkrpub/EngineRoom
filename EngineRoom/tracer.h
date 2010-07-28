/*
 *  $Id: tracer.h 755 2009-02-02 12:18:17Z bkr $
 *
 *  Copyright (c) 2007 Bjoern Kriews
 */

#ifndef __TRACER_H__
#define __TRACER_H__ 1

#include "er_util.h"

#ifdef __APPLE__
/* available in OS X >= 10.5 */
extern int backtrace(void**,int) __attribute__((weak_import));
extern char** backtrace_symbols(void* const*,int) __attribute__((weak_import));
extern void backtrace_symbols_fd(void* const*,int,int) __attribute__((weak_import));

//extern int backtrace_via_NSException(void **pcs, int size);
extern int backtrace_via_builtin_return_address(void **pcs, int size);

#define TRACER_BACKTRACE(pcs, size) ((backtrace ? backtrace : backtrace_via_builtin_return_address)((pcs), (size))) 

#else
#include <execinfo.h>
#define TRACER_BACKTRACE(pcs, size) backtrace((pcs), (size))
#endif

#ifndef TRACER_DEBUG
#define TRACER_DEBUG 0
#endif

#ifndef TRACER_DEBUG_FAT
#if TRACER_DEBUG
#define TRACER_DEBUG_FAT 1
#else
#define TRACER_DEBUG_FAT 0
#endif
#endif

#ifndef TRACER_DEBUG_MACHO
#if TRACER_DEBUG
#define TRACER_DEBUG_MACHO 1
#else
#define TRACER_DEBUG_MACHO 0
#endif
#endif

#ifndef TRACER_DEBUG_SYM
#if TRACER_DEBUG
#define TRACER_DEBUG_SYM 1
#else
#define TRACER_DEBUG_SYM 0
#endif
#endif

#ifndef TRACER_DEBUG_SYM_HEAVY
#define TRACER_DEBUG_SYM_HEAVY 0
#endif

#ifndef TRACER_DEBUG_STORE
#if TRACER_DEBUG
#define TRACER_DEBUG_STORE 1
#else
#define TRACER_DEBUG_STORE 0
#endif
#endif

#ifndef TRACER_DEBUG_LOOKUP
#if TRACER_DEBUG
#define TRACER_DEBUG_LOOKUP 1
#else
#define TRACER_DEBUG_LOOKUP 0
#endif
#endif

/* list of symbols to restrict heavy debug output to - i.e.: */
/* #define TRACER_DEBUG_LIMIT "_start _main __nsnote_callback _tracerDumpBacktrace" */

#define TRACER_SUCCESS 0
#define TRACER_FAILURE 1

#define TRACER_OPT_DEFAULT 0

typedef struct tracerSymbol {
  uint32_t strtab_index;
  uint32_t strtab_imagePath_index;
  uint32_t strtab_imageName_index;
  uint64_t value;

} TRACER_SYMBOL;


typedef struct tracerSymbolStore {
  TRACER_SYMBOL *symbols;
  uint32_t symbols_size;
  uint32_t symbols_capacity;
  uint32_t symbols_capacity_growth;

  const char *strtab;
  uint32_t strtab_size;
  uint32_t strtab_capacity;
  uint32_t strtab_capacity_growth;

  /* used internally while collecting */
  const char *current_imagePath;
  uint32_t current_strtab_imageName_index;
  uint32_t current_strtab_imagePath_index;

} TRACER_SYMBOL_STORE;

#ifdef __TRACER_C__
#define TRACER_EXPORT /**/
#else
#define TRACER_EXPORT extern
#endif

typedef int (*TRACER_SYMBOL_WORKER)(const char *imagePath, const char *symbolName, uint64_t symbolAddress, void *workerInfo, uint64_t options);
typedef int (*TRACER_SYMBOL_SORTER)(void *sorterInfo, const TRACER_SYMBOL *a, const TRACER_SYMBOL *b);

TRACER_EXPORT int tracerAnalyzeFile(UTIL_MACH_HEADER *mhp, const char *imageName, intptr_t slide, TRACER_SYMBOL_WORKER symbolAction, void *symbolActionInfo, uint64_t options);
TRACER_EXPORT int tracerAnalyzeMachO(UTIL_MACH_HEADER *mhp, const char *imageName, UTIL_MACH_HEADER *live_mhp, TRACER_SYMBOL_WORKER symbolAction, void *symbolActionInfo, uint64_t options );
TRACER_EXPORT int tracerWalkSymbolTables(TRACER_SYMBOL_WORKER symbolAction, void *symbolActionInfo, uint64_t options );

/*
 * symbol store management
 */
TRACER_EXPORT int tracerSymbolStoreCollector(const char *imageName, const char *name, uint64_t value, void *info, uint64_t options);

TRACER_EXPORT TRACER_SYMBOL_STORE *tracerSymbolStoreCollect(uint64_t options, TRACER_SYMBOL_SORTER sorter, void *sorterInfo);

TRACER_EXPORT TRACER_SYMBOL_STORE *tracerSymbolStoreForLookupByAddress(void);

TRACER_EXPORT int tracerSymbolStoreInit( TRACER_SYMBOL_STORE *store );
TRACER_EXPORT uint32_t tracerSymbolStoreCount( TRACER_SYMBOL_STORE *store );

TRACER_EXPORT const char *tracerSymbolStoreNameOfSymbol( TRACER_SYMBOL_STORE *store, TRACER_SYMBOL *symbol );
TRACER_EXPORT const char *tracerSymbolStoreImageNameOfSymbol( TRACER_SYMBOL_STORE *store, TRACER_SYMBOL *symbol );
TRACER_EXPORT const char *tracerSymbolStoreImagePathOfSymbol( TRACER_SYMBOL_STORE *store, TRACER_SYMBOL *symbol );

TRACER_EXPORT int tracerSymbolStoreShow( TRACER_SYMBOL_STORE *store );
TRACER_EXPORT int tracerSymbolStoreShowContents( TRACER_SYMBOL_STORE *store );

TRACER_EXPORT int tracerSymbolStoreSorterByAddress( void *sorterInfo, const TRACER_SYMBOL *a, const TRACER_SYMBOL *b );
TRACER_EXPORT int tracerSymbolStoreSort( TRACER_SYMBOL_STORE *store, TRACER_SYMBOL_SORTER sorter, void *sorterInfo );

TRACER_EXPORT int tracerSymbolStoreLookupByAddress( TRACER_SYMBOL_STORE *store, uint64_t address, TRACER_SYMBOL **symbolPtr, uint64_t *offsetPtr );

TRACER_EXPORT TRACER_SYMBOL_STORE *tracerSymbolStoreAllocate(void);
TRACER_EXPORT void tracerSymbolStoreRelease( TRACER_SYMBOL_STORE *store );

TRACER_EXPORT void _tracerDump(int skipframes, void **pcs, int frames);

#define tracerDump() ({ \
  void *__pcs[64]; _tracerDump( 0 /*skipframes*/, __pcs, TRACER_BACKTRACE(__pcs, sizeof(__pcs)/sizeof(*__pcs))); })

TRACER_EXPORT int tracerCTest(int argc, const char **argv);


/*
 * support for gcc -finstrument-functions
 */

typedef struct tracerEvent {
  unsigned long eventType;
  void *function;
  void *call_site;
  void *thread;
} TRACER_EVENT;


#define TRACER_EVENT_VERSION 1

#define TRACER_EVENT_TYPE_MAGIC_32 0xdecafbadUL
#ifdef UTIL_64BIT
#define TRACER_EVENT_TYPE_MAGIC_64 0xbadcafe0babedeadUL
#define TRACER_EVENT_TYPE_BEGIN TRACER_EVENT_TYPE_MAGIC_64
#else
#define TRACER_EVENT_TYPE_MAGIC_64 0xbadcafe0babedeadULL
#define TRACER_EVENT_TYPE_BEGIN TRACER_EVENT_TYPE_MAGIC_32
#endif

#define TRACER_EVENT_TYPE_END   'E'
#define TRACER_EVENT_TYPE_ENTER 'I'
#define TRACER_EVENT_TYPE_EXIT  'O'

void tracerStartInstrumentation(void);
void tracerStopInstrumentation(void);
void tracerInstrumentationEvent(unsigned long eventType, void *this_fn, void *call_site);

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import <objc/runtime.h>

typedef struct tracerRuntimeScannerInfo {
  TRACER_SYMBOL_STORE *symbolStore;

  uint32_t classCount;
  uint32_t methodCount;
        
  NSMutableArray *classArray;
  NSMutableArray *methodArray;
  NSMutableDictionary *classDictionary;
  NSArray *sortedIMPs;
        
  // internal 
  NSString *currentClassName;
  NSMutableArray *currentMethodArray;
        
  uint64_t searchAddress;
  uint64_t offset;
  uint64_t nearestSymbolAddress;
  NSString *nearestSymbol;
  Class nearestClass;
  SEL nearestSel;

  NSString *imagePath;

} TRACER_RUNTIME_SCANNER_INFO;

TRACER_EXPORT void tracerRuntimeScannerInfoInit(TRACER_RUNTIME_SCANNER_INFO *info);

TRACER_EXPORT void tracerScanMethodList(Class aClass, TRACER_RUNTIME_SCANNER_INFO *info);
TRACER_EXPORT BOOL tracerScanClassList(TRACER_RUNTIME_SCANNER_INFO *info);

// keys for frame info dictionaries returned by tracerFrameInfoForAddress
TRACER_EXPORT NSString *kTracerAddress;
TRACER_EXPORT NSString *kTracerSymbolOffset;
TRACER_EXPORT NSString *kTracerSymbolAddress;
TRACER_EXPORT NSString *kTracerSymbolName;
TRACER_EXPORT NSString *kTracerClassName;
TRACER_EXPORT NSString *kTracerSelectorName;
TRACER_EXPORT NSString *kTracerIsClassMethod;
TRACER_EXPORT NSString *kTracerImagePath;
TRACER_EXPORT NSString *kTracerImageName;

TRACER_EXPORT NSDictionary *tracerFrameInfoForAddress(uint64_t theAddress, TRACER_RUNTIME_SCANNER_INFO *info);

TRACER_EXPORT NSArray *_tracerBacktraceAsArrayOfDictionaries(int skipframes, void **pcs, int frames);
TRACER_EXPORT NSArray *_tracerBacktraceAsArrayOfStrings(NSArray *traceDictionaries);

#define tracerBacktraceAsArrayOfDictionaries(skipframes) \
	({ void *__pcs[64]; _tracerBacktraceAsArrayOfDictionaries( skipframes, __pcs, TRACER_BACKTRACE(__pcs, sizeof(__pcs)/sizeof(*__pcs))); })

#define tracerBacktraceAsArrayOfStrings(skipframes) \
	_tracerBacktraceAsArrayOfStrings( tracerBacktraceAsArrayOfDictionaries(skipframes) )

#define tracerBacktraceAsString(skipframes) \
	( [[tracerBacktraceAsArrayOfStrings(skipframes) componentsJoinedByString: @"\n"] stringByAppendingString: @"\n"] )

#define tracerDumpBacktrace(skipframes) NSLog(@"\nBacktrace:\n%@\n", tracerBacktraceAsString(0) )

TRACER_EXPORT int tracerObjCTest(int argc, const char **argv);

#endif
/* __OBJC__ */

#endif 
/* __TRACER_H__ */


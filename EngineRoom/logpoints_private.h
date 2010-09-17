/*
 *  $Id: logpoints_private.h 760 2009-02-11 01:24:39Z bkr $
 *
 *  Copyright (c) 2007 Bjoern Kriews
 */

#ifndef __LOGPOINTS_PRIVATE_H__
#define __LOGPOINTS_PRIVATE_H__ 1

#include "er_util.h"
#include "logpoints_types.h"

#import <stdlib.h>
#import <unistd.h>
#import <sys/types.h>
#import <inttypes.h>

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

#ifdef NO_LACK_OF_CONCEPT

#ifndef LOGPOINT_COUNT
#ifdef LOGPOINT_RELEASE_BUILD
#define LOGPOINT_COUNT 0
#else
#define LOGPOINT_COUNT 1
#endif
#endif

#ifndef LOGPOINT_ENABLE_DEBUG
#ifdef LOGPOINT_RELEASE_BUILD
#define LOGPOINT_ENABLE_DEBUG 0
#else
#define LOGPOINT_ENABLE_DEBUG 1
#endif
#endif

#ifndef LOGPOINT_ENABLE_TRACE
#ifdef LOGPOINT_RELEASE_BUILD
#define LOGPOINT_ENABLE_TRACE 0
#else
#define LOGPOINT_ENABLE_TRACE 1
#endif
#endif

#ifndef LOGPOINT_ENABLE_WARNING
#define LOGPOINT_ENABLE_WARNING 1
#endif

#ifndef LOGPOINT_ENABLE_ASSERT
#define LOGPOINT_ENABLE_ASSERT 1
#endif

#ifndef LOGPOINT_ENABLE_NOTES
#ifdef LOGPOINT_RELEASE_BUILD
#define LOGPOINT_ENABLE_NOTES 0
#else
#define LOGPOINT_ENABLE_NOTES 1
#endif
#endif

#ifndef LOGPOINT_ENABLE_SWITCH
#define LOGPOINT_ENABLE_SWITCH 1
#endif

#endif
/* NO_LACK_OF_CONCEPT */

#ifndef LOGPOINT_EMPTY
#define LOGPOINT_EMPTY ({ })
#endif

#ifdef __linux__
#define LOGPOINT_SECTION "__lpts"
#define LOGPOINT_SECTION_ATTRIBUTE __attribute__(( used, section("__lpts") ))
#define LOGPOINT_USE_ELF 1
#endif

#ifdef __APPLE__
#define LOGPOINT_SEGMENT "__DATA"
#define LOGPOINT_SECTION "__lpts"
#define LOGPOINT_SECTION_ATTRIBUTE __attribute__(( used, section("__DATA,__lpts") ))
#endif

#ifdef __sun
#define LOGPOINT_SECTION "__lpts"
#ifdef __GNUC__
#define LOGPOINT_SECTION_ATTRIBUTE __attribute__(( used, section("__lpts") ))
#else
#define LOGPOINT_SECTION_ATTRIBUTE __attribute__(( section("__lpts") ))
#endif

#define LOGPOINT_USE_ELF 1
#endif

#ifndef LOGPOINT_SECTION_ATTRIBUTE
#error LOGPOINT_SECTION_ATTRIBUTE not defined for this architecture
#endif

#define LOGPOINT_METHODTYPE_FUNCTION    0
#define LOGPOINT_METHODTYPE_CLASS       '+'
#define LOGPOINT_METHODTYPE_INSTANCE    '-'

#if LOGPOINT_COUNT
#define LOGPOINT_INCREMENT_COUNTER  ++lplogpoint.count
#else
#define LOGPOINT_INCREMENT_COUNTER  LOGPOINT_EMPTY
#endif

/* override this with your own -D if you need to */
#ifndef LOGPOINT_INVOKE
#define LOGPOINT_INVOKE(lpp, langspec1, langspec2, fmt, ...) (*logPointGetInvoker())((lpp), (langspec1), (langspec2), (fmt), ## __VA_ARGS__ )
#endif

#if __clang__
//#warning Disabling LOGPOINT_USE_LOCAL_LABEL because (as of 20100809, Apple clang version 2.0 [108.3]) it is not supported by clang, see http://llvm.org/bugs/show_bug.cgi?id=3429
#undef LOGPOINT_USE_LOCAL_LABEL
#define LOGPOINT_USE_LOCAL_LABEL 0
#endif

#ifndef LOGPOINT_USE_LOCAL_LABEL
#define LOGPOINT_USE_LOCAL_LABEL 1
#endif

#if LOGPOINT_USE_LOCAL_LABEL
#define LOGPOINT_LOCAL_LABEL_DECLARATION __label__ lplabel;
#define LOGPOINT_LOCAL_LABEL_CREATE      lplabel:
#define LOGPOINT_LOCAL_LABEL_ADDRESS     &&lplabel
#else
#define LOGPOINT_LOCAL_LABEL_DECLARATION /**/
#define LOGPOINT_LOCAL_LABEL_CREATE      /**/
#define LOGPOINT_LOCAL_LABEL_ADDRESS     NULL
#endif

#define LOGPOINT_CREATE(theFlags, kind, keys, label, langspec1, langspec2, fmt, ...) ({ \
        LOGPOINT_LOCAL_LABEL_DECLARATION /* must come first - see gcc docs */ \
        static LOGPOINT lplogpoint LOGPOINT_SECTION_ATTRIBUTE = \
	  { LOGPOINT_MAGIC, sizeof(LOGPOINT), (kind), (keys), __UTIL_PRETTY_FUNCTION__, __FILE__, __LINE__, \
	    (theFlags), (LOGPOINT_COUNT) ? 0 : LOGPOINT_NOT_COUNTED, NULL, LOGPOINT_LOCAL_LABEL_ADDRESS, label, #fmt ", " #__VA_ARGS__, NULL, 0 /*resv*/, LOGPOINT_MAGIC2(__LINE__) }; \
        LOGPOINT_LOCAL_LABEL_CREATE /* after the static - or gcc 4.0.1 will crash */ \
        LOGPOINT_INCREMENT_COUNTER; \
        if( LOGPOINT_IS_ACTIVE(lplogpoint) ) { \
			LOGPOINT_INVOKE(&lplogpoint, langspec1, langspec2, fmt, ## __VA_ARGS__); \
        } \
		LOGPOINT_IS_ACTIVE(lplogpoint); /* return value - to be able to detect logpoint activeness in code */ \
})

/* functions used by the logpoints */

lp_return_t logPointApplyToData(
				  const char *imageName,
				  LOGPOINT *logpts,
				  size_t logSizeInBytes, 
				  LOGPOINT_FILTER filter, 
				  void *filterInfo,
				  LOGPOINT_WORKER action, 
				  void *actionInfo,
				  lp_uint_t options
				  );


lp_return_t logPointPlatformApply(LOGPOINT_FILTER filter, void *filterInfo, LOGPOINT_WORKER action, void *actionInfo, lp_uint_t options);

#endif 
/* __LOGPOINTS_PRIVATE_H__ */


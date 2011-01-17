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

#ifndef __LOGPOINTS_PRIVATE_H__
#define __LOGPOINTS_PRIVATE_H__ 1

#include "er_util.h"
#include "er_macros.h"
#include "logpoints_types.h"

#import <stdlib.h>
#import <unistd.h>
#import <sys/types.h>
#import <inttypes.h>

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

#ifndef LOGPOINT_NOP
#define LOGPOINT_NOP ({ }) 
#endif

#ifndef LOGPOINT_ZERO
#define LOGPOINT_ZERO logPointReturnFromMacro(NULL) /* logpoints return whether they were triggered */
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
#if LOGPOINT_COUNT_INACTIVE
#define LOGPOINT_INCREMENT_COUNTER_ALWAYS    ++lplogpoint.count
#define LOGPOINT_INCREMENT_COUNTER_IF_ACTIVE LOGPOINT_NOP
#else
#define LOGPOINT_INCREMENT_COUNTER_ALWAYS    LOGPOINT_NOP
#define LOGPOINT_INCREMENT_COUNTER_IF_ACTIVE ++lplogpoint.count
#endif
#else
#define LOGPOINT_INCREMENT_COUNTER_ALWAYS    LOGPOINT_NOP
#define LOGPOINT_INCREMENT_COUNTER_IF_ACTIVE LOGPOINT_NOP
#endif

#ifndef LOGPOINT_INVOKE
#define LOGPOINT_INVOKE(lpp, langSpec1, langSpec2, fmt, ...) ( \
	NULL == ER_ADDRESS_OF_GLOBAL_OR_EMBEDDED( logPointGetInvoker ) ? LOGPOINT_NO : \
	(ER_ADDRESS_OF_GLOBAL_OR_EMBEDDED( logPointGetInvoker )())((lpp), (langSpec1), (langSpec2), (fmt), ## __VA_ARGS__ ) )
#endif


#if __clang__
#if MAINTAINER_WARNINGS
#warning Disabling LOGPOINT_USE_LOCAL_LABEL because (as of 20100809, Apple clang version 2.0 [108.3]) it is not supported by clang, see http://llvm.org/bugs/show_bug.cgi?id=3429
#endif
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

/*! 
	@function LOGPOINT_CREATE
	@abstract Lowest-level logpoint creation macro
	@discussion Creates a static struct LOGPOINT mapped into a special linker segment
	@param flags bitwise-or of logpoint flags
	@param kind  compile-time constant char pointer, describing the kind of logpoint or kLogPointKindNone
	@param keys  compile-time constant char pointer, points to comma separated keywords (spaces optional) associated with the logpoint or kLogPointKeysNone
	@param label compile-time constant char pointer, extra label to decorate the message with
*/	

/* clang doesn't like it if we don't use the result of ({ }) expressions -
   I found no way to #pragma it away and I don't want to force anybody to disable warnings
 */
static inline LOGPOINT *logPointReturnFromMacro( LOGPOINT *lpp ) { return lpp; }

#if MAINTAINER_WARNINGS
#warning BK: The return value from the invoker is ignored. This is because we want to return &lp for switches if ACTIVE. But it hides i.e. printf fail on disk full
#endif	

#define LOGPOINT_CREATE(flags, kind, keys, label, langSpec1, langSpec2, formatInfo, fmt, ...) ({ \
        LOGPOINT_LOCAL_LABEL_DECLARATION /* must come first - see gcc docs */ \
        static LOGPOINT lplogpoint LOGPOINT_SECTION_ATTRIBUTE = \
	  { LOGPOINT_MAGIC, sizeof(LOGPOINT), (kind), (keys), __UTIL_PRETTY_FUNCTION__, __FILE__, __LINE__, \
	    (flags), (LOGPOINT_COUNT) ? 0 : LOGPOINT_NOT_COUNTED, NULL, LOGPOINT_LOCAL_LABEL_ADDRESS, (label), (formatInfo) ?: ( (fmt) ? #fmt ", " #__VA_ARGS__ : NULL ), NULL, 0 /*resv*/, LOGPOINT_MAGIC2(__LINE__) }; \
        LOGPOINT_LOCAL_LABEL_CREATE /* after the static - or gcc 4.0.1 will crash */ \
        LOGPOINT_INCREMENT_COUNTER_ALWAYS; \
		LOGPOINT *__lpResult = NULL;	\
        if( LOGPOINT_IS_ACTIVE(lplogpoint) ) { \
			LOGPOINT_INCREMENT_COUNTER_IF_ACTIVE; \
          (void) LOGPOINT_INVOKE(&lplogpoint, langSpec1, langSpec2, fmt, ## __VA_ARGS__); \
          __lpResult = &lplogpoint; /* non-NULL return signifies an active logpoint */ \
        } \
	logPointReturnFromMacro( __lpResult );	\
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


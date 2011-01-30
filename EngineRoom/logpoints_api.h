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

#ifndef __LOGPOINTS_API_H__
#define __LOGPOINTS_API_H__ 1

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#endif

#include "er_symbols.h"

#include "logpoints_types.h"
#include "logpoints_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __LOGPOINTS_C__
#define LOGPOINTS_EXPORT			/**/
#define LOGPOINTS_EXPORT_EMBEDDED	/**/
#else
#define LOGPOINTS_EXPORT			extern
#define LOGPOINTS_EXPORT_EMBEDDED	extern
#endif

#ifndef LOGPOINT_INVOKER_STACKBUFFER
#define LOGPOINT_INVOKER_STACKBUFFER 1024
#endif
	
#ifndef LOGPOINT_EMITTER_STACKBUFFER
#define LOGPOINT_EMITTER_STACKBUFFER 1536
#endif
	
#ifndef LOGPOINT_MAX_DECORATION_LENGTH
#define LOGPOINT_MAX_DECORATION_LENGTH 512
#endif	

LOGPOINTS_EXPORT const char * logPointEmbeddedName(void) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT lp_uint_t logPointDataFormat(void) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT const char * logPointLibraryVersion(void) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT const char * logPointLibraryIdentifier(void) ER_SYMBOL_WEAK_IMPORT;
	
LOGPOINTS_EXPORT const char *logPointLastPathComponent(const char *path) ER_SYMBOL_WEAK_IMPORT;

/* error description from lp_return_t */
LOGPOINTS_EXPORT const char *logPointReturnString(lp_return_t err) ER_SYMBOL_WEAK_IMPORT;

LOGPOINTS_EXPORT lp_return_t logPointReset(void) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT lp_return_t logPointEnableSimple(const char *filter) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT lp_return_t logPointDisableSimple(const char *filter) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT lp_return_t logPointApplySimple(const char *filter, lp_uint_t options) ER_SYMBOL_WEAK_IMPORT;

LOGPOINTS_EXPORT lp_return_t logPointApply( LOGPOINT_FILTER filter, void *filterInfo, LOGPOINT_WORKER action, void *actionInfo, lp_uint_t options ) ER_SYMBOL_WEAK_IMPORT;

LOGPOINTS_EXPORT lp_return_t logPointDumpAll(void) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT lp_return_t logPointActionDump(LOGPOINT *lp, void *actionInfo) ER_SYMBOL_WEAK_IMPORT;

LOGPOINTS_EXPORT lp_return_t logPointDumpAllWithFormat(const char *format) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT lp_return_t logPointActionDumpWithFormat(LOGPOINT *lpp, void *actionInfo) ER_SYMBOL_WEAK_IMPORT;
	
LOGPOINTS_EXPORT int         logPointFilterSimple(LOGPOINT *lp, void *filterInfo) ER_SYMBOL_WEAK_IMPORT;

LOGPOINTS_EXPORT const char *logPointPriorityNameFromNumber(lp_uint_t priority) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT lp_uint_t logPointPriorityNumberFromName(const char *name) ER_SYMBOL_WEAK_IMPORT;

LOGPOINTS_EXPORT lp_return_t logPointApplyToData(const char *imageName, LOGPOINT *logpts, size_t logSizeInBytes,  LOGPOINT_FILTER filter, void *filterInfo, LOGPOINT_WORKER action, void *actionInfo, lp_uint_t options) ER_SYMBOL_WEAK_IMPORT;	
LOGPOINTS_EXPORT lp_return_t logPointPlatformApply( LOGPOINT_FILTER filter, void *filterInfo, LOGPOINT_WORKER action, void *actionInfo, lp_uint_t options ) ER_SYMBOL_WEAK_IMPORT;

#ifdef ER_EMBEDDED_NAME
LOGPOINTS_EXPORT_EMBEDDED const char * ER_SYMBOL_EMBEDDED_NAME( logPointEmbeddedName )(void);
LOGPOINTS_EXPORT_EMBEDDED lp_uint_t ER_SYMBOL_EMBEDDED_NAME( logPointDataFormat )(void);
LOGPOINTS_EXPORT_EMBEDDED const char * ER_SYMBOL_EMBEDDED_NAME( logPointLibraryVersion )(void);
LOGPOINTS_EXPORT_EMBEDDED const char * ER_SYMBOL_EMBEDDED_NAME( logPointLibraryIdentifier )(void);

LOGPOINTS_EXPORT_EMBEDDED const char * ER_SYMBOL_EMBEDDED_NAME( logPointLastPathComponent )(const char *path);

LOGPOINTS_EXPORT_EMBEDDED const char * ER_SYMBOL_EMBEDDED_NAME( logPointReturnString )(lp_return_t err);
LOGPOINTS_EXPORT_EMBEDDED lp_return_t ER_SYMBOL_EMBEDDED_NAME( logPointReset )(void);
LOGPOINTS_EXPORT_EMBEDDED lp_return_t ER_SYMBOL_EMBEDDED_NAME( logPointEnableSimple )(const char *filter);
LOGPOINTS_EXPORT_EMBEDDED lp_return_t ER_SYMBOL_EMBEDDED_NAME( logPointDisableSimple )(const char *filter);
LOGPOINTS_EXPORT_EMBEDDED lp_return_t ER_SYMBOL_EMBEDDED_NAME( logPointApplySimple )(const char *filter, lp_uint_t options);
LOGPOINTS_EXPORT_EMBEDDED lp_return_t ER_SYMBOL_EMBEDDED_NAME( logPointApply )( LOGPOINT_FILTER filter, void *filterInfo, LOGPOINT_WORKER action, void *actionInfo, lp_uint_t options );
LOGPOINTS_EXPORT_EMBEDDED lp_return_t ER_SYMBOL_EMBEDDED_NAME( logPointDumpAllWithFormat )(const char *format);
LOGPOINTS_EXPORT_EMBEDDED lp_return_t ER_SYMBOL_EMBEDDED_NAME( logPointActionDumpWithFormat )(LOGPOINT *lpp, void *actionInfo);
LOGPOINTS_EXPORT_EMBEDDED lp_return_t ER_SYMBOL_EMBEDDED_NAME( logPointDumpAll )(void);
LOGPOINTS_EXPORT_EMBEDDED lp_return_t ER_SYMBOL_EMBEDDED_NAME( logPointActionDump )(LOGPOINT *lpp, void *actionInfo);
LOGPOINTS_EXPORT_EMBEDDED int ER_SYMBOL_EMBEDDED_NAME( logPointFilterSimple )(LOGPOINT *lpp, void *filterInfo);

LOGPOINTS_EXPORT_EMBEDDED const char * ER_SYMBOL_EMBEDDED_NAME( logPointPriorityNameFromNumber )(lp_uint_t priority);
LOGPOINTS_EXPORT_EMBEDDED lp_uint_t ER_SYMBOL_EMBEDDED_NAME( logPointPriorityNumberFromName )(const char *name);

LOGPOINTS_EXPORT_EMBEDDED lp_return_t ER_SYMBOL_EMBEDDED_NAME( logPointApplyToData )(const char *imageName, LOGPOINT *logpts, size_t logSizeInBytes,  LOGPOINT_FILTER filter, void *filterInfo, LOGPOINT_WORKER action, void *actionInfo, lp_uint_t options);	
LOGPOINTS_EXPORT_EMBEDDED lp_return_t ER_SYMBOL_EMBEDDED_NAME( logPointPlatformApply )( LOGPOINT_FILTER filter, void *filterInfo, LOGPOINT_WORKER action, void *actionInfo, lp_uint_t options );
	
	
#endif


/* used as a return from filter functions and invocations */
#define LOGPOINT_YES				1
#define LOGPOINT_NO				0

/* used as a return from worker functions */
#define LOGPOINT_RETURN_STOP            1

/* error return codes */
#define LOGPOINT_RETURN_OK               0
#define LOGPOINT_RETURN_BAD_ALIGNMENT    (-1)
#define LOGPOINT_RETURN_BAD_MAGIC        (-2)
#define LOGPOINT_RETURN_BAD_SIZE         (-3)
#define LOGPOINT_RETURN_BAD_STRUCTURE    (-4)
#define LOGPOINT_RETURN_UNEXPECTED_SIZE  (-5)
#define LOGPOINT_RETURN_NO_IMAGE_LIST    (-6)
#define LOGPOINT_RETURN_NO_IMAGE_NAME    (-7)
#define LOGPOINT_RETURN_BAD_FILTER       (-8)

/* options for logpoint functions */

#define LOGPOINT_OPTION_NONE		    0

#define LOGPOINT_OPTION_STATIC_ONLY         (1 << 0)
#define LOGPOINT_OPTION_DYNAMIC_ONLY        (1 << 1)

/* used internally */
#define LOGPOINT_OPTION_WALKING_DYNAMIC     (1 << 2)

#define LOGPOINT_OPTION_IGNORE_HARD         (1 << 3)

/* quick actions - action may be null or will be executed afterwards */
#define LOGPOINT_OPTION_DISABLE              (1 << 4)
#define LOGPOINT_OPTION_ENABLE               (1 << 5)


/*
 *
 * types and functions for implementing custom logpoint handlers
 *
 */

/*
 * all code that uses or declares these types must be compiled in the same language
 */
#ifdef __OBJC__
typedef CFStringRef LOGPOINT_MESSAGE_TYPE;
#define LOGPOINT_MESSAGE_FORMAT "%@"
#define LOGPOINT_MESSAGE_EMPTY  CFSTR("")
#else
typedef char *LOGPOINT_MESSAGE_TYPE;
#define LOGPOINT_MESSAGE_FORMAT "%s"
#define LOGPOINT_MESSAGE_EMPTY  ""
#endif

	
LOGPOINTS_EXPORT void * logPointAllocateBufferIfNeeded( void *existingBuffer, size_t existingBufferSize, size_t wantedSize ) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT void logPointFreeBufferIfNeeded( void *buffer, void *existingBuffer ) ER_SYMBOL_WEAK_IMPORT;

#ifdef ER_EMBEDDED_NAME	
LOGPOINTS_EXPORT_EMBEDDED void * ER_SYMBOL_EMBEDDED_NAME( logPointAllocateBufferIfNeeded )( void *existingBuffer, size_t existingBufferSize, size_t wantedSize );
LOGPOINTS_EXPORT_EMBEDDED void ER_SYMBOL_EMBEDDED_NAME( logPointFreeBufferIfNeeded )( void *buffer, void *existingBuffer );
#endif
	
/*
 * this is the first function invoked by a logpoint, full control, all responsibilities yours
 * if you don't care about ObjC, you can assume that "fmt" is const char *, otherwise it is
 * LOGPOINT_FLAG(*lpp, LOGPOINT_NSSTRING) ? CFStringRef : const char *
 */
typedef lp_return_t (*LOGPOINT_INVOKER)(LOGPOINT *lpp, const void *langSpec1, const void *langSpec2, const void *fmt, ...);
#define LOGPOINT_INVOKER_DECLARATION(name) lp_return_t name(LOGPOINT *lpp, const void *langSpec1, const void *langSpec2, const void *fmt, ...)

LOGPOINTS_EXPORT LOGPOINT_INVOKER_DECLARATION( logPointInvokerDefault ) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT LOGPOINT_INVOKER logPointGetInvoker(void) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT LOGPOINT_INVOKER logPointSetInvoker(LOGPOINT_INVOKER newInvoker) ER_SYMBOL_WEAK_IMPORT;

#ifdef ER_EMBEDDED_NAME
LOGPOINTS_EXPORT_EMBEDDED LOGPOINT_INVOKER_DECLARATION( ER_SYMBOL_EMBEDDED_NAME( logPointInvokerDefault ) );	
LOGPOINTS_EXPORT_EMBEDDED LOGPOINT_INVOKER ER_SYMBOL_EMBEDDED_NAME( logPointGetInvoker )(void);
LOGPOINTS_EXPORT_EMBEDDED LOGPOINT_INVOKER ER_SYMBOL_EMBEDDED_NAME( logPointSetInvoker )(LOGPOINT_INVOKER newInvoker);
#endif
	
/*
 * payload is the result of the users "fmt", ... arguments
 * if the ObjC version (logpoints.m) is used, payload is a CFStringRef, otherwise a const char *
 */
typedef lp_return_t (*LOGPOINT_COMPOSER)(LOGPOINT *lpp, const void *langSpec1, const void *langSpec2, const char *payload);

#define LOGPOINT_COMPOSER_DECLARATION(name) lp_return_t name(LOGPOINT *lpp, const void *langSpec1, const void *langSpec2, const char *payload)

LOGPOINTS_EXPORT LOGPOINT_COMPOSER_DECLARATION( logPointComposerDefault ) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT LOGPOINT_COMPOSER logPointGetComposer(void) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT LOGPOINT_COMPOSER logPointSetComposer(LOGPOINT_COMPOSER newComposer) ER_SYMBOL_WEAK_IMPORT;

#ifdef ER_EMBEDDED_NAME
LOGPOINTS_EXPORT_EMBEDDED LOGPOINT_COMPOSER_DECLARATION( ER_SYMBOL_EMBEDDED_NAME( logPointComposerDefault ) );	
LOGPOINTS_EXPORT_EMBEDDED LOGPOINT_COMPOSER ER_SYMBOL_EMBEDDED_NAME( logPointGetComposer )(void);
LOGPOINTS_EXPORT_EMBEDDED LOGPOINT_COMPOSER ER_SYMBOL_EMBEDDED_NAME( logPointSetComposer )(LOGPOINT_COMPOSER newComposer);
#endif
	
	
/*
 * the composer will call the emitter with a format string and arguments decorating
 * the message produced by the invoker with metadata like location in source etc.
 */
typedef lp_return_t (*LOGPOINT_EMITTER)(LOGPOINT *lpp, const void *langSpec1, const void *langSpec2, const char *logFormat, const char *payload);

#define LOGPOINT_EMITTER_DECLARATION(name) lp_return_t name(LOGPOINT *lpp, const void *langSpec1, const void *langSpec2, const char *logFormat, const char *payload)

LOGPOINTS_EXPORT_EMBEDDED LOGPOINT_EMITTER_DECLARATION( logPointEmitterDefault ) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT_EMBEDDED LOGPOINT_EMITTER logPointGetEmitter(void) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT_EMBEDDED LOGPOINT_EMITTER logPointSetEmitter(LOGPOINT_EMITTER newEmitter) ER_SYMBOL_WEAK_IMPORT;

#ifdef ER_EMBEDDED_NAME
	LOGPOINTS_EXPORT_EMBEDDED LOGPOINT_EMITTER_DECLARATION( ER_SYMBOL_EMBEDDED_NAME( logPointEmitterDefault ) );	
	LOGPOINTS_EXPORT_EMBEDDED LOGPOINT_EMITTER ER_SYMBOL_EMBEDDED_NAME( logPointGetEmitter )(void);
	LOGPOINTS_EXPORT_EMBEDDED LOGPOINT_EMITTER ER_SYMBOL_EMBEDDED_NAME( logPointSetEmitter )(LOGPOINT_EMITTER newEmitter);
#endif

/*
 * the formatter will produce the final output decorated with metadata
 */
typedef size_t (*LOGPOINT_FORMATTERV)( LOGPOINT *lpp, const void *langSpec1, const void *langSpec2, char *buffer, size_t bufferSize, const void *extensions, void *userInfo, const char *format, va_list args);
typedef size_t (*LOGPOINT_FORMATTER) ( LOGPOINT *lpp, const void *langSpec1, const void *langSpec2, char *buffer, size_t bufferSize, const void *extensions, void *userInfo, const char *format, ...);	

#define LOGPOINT_FORMATTERV_DECLARATION(name) size_t name(LOGPOINT *lpp, const void *langSpec1, const void *langSpec2, char *buffer, size_t bufferSize, const void *extensions, void *userInfo, const char *format, va_list args)
#define LOGPOINT_FORMATTER_DECLARATION(name)  size_t name(LOGPOINT *lpp, const void *langSpec1, const void *langSpec2, char *buffer, size_t bufferSize, const void *extensions, void *userInfo, const char *format, ...)	
	
typedef const char * (*LOGPOINT_FORMAT_FUNCTION)(LOGPOINT *lpp, const void *langSpec1, const void *langSpec2, char *buffer, size_t bufferSize, const void *extensions, void *userInfo, const char *fmt, ...);

#define LOGPOINT_FORMAT_FUNCTION_DECLARATION(name) const char *name(LOGPOINT *lpp, const void *langSpec1, const void *langSpec2, char *buffer, size_t bufferSize, const void *extensions, void *userInfo, const char *fmt, ...)
	
/*
 * these functions produce a textual description of a logpoint
 * callable with langspec1/2 during invocation and without i.e. for display
 * the extension, userInfo and arguments following format are currently unused
 */


LOGPOINTS_EXPORT LOGPOINT_FORMATTERV_DECLARATION( logPointFormatterVDefault ) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT LOGPOINT_FORMATTER_DECLARATION( logPointFormat ) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT LOGPOINT_FORMATTERV logPointGetFormatterV(void) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT LOGPOINT_FORMATTERV logPointSetFormatterV(LOGPOINT_FORMATTERV newFormatterV) ER_SYMBOL_WEAK_IMPORT;

#ifdef ER_EMBEDDED_NAME
	LOGPOINTS_EXPORT_EMBEDDED LOGPOINT_FORMATTERV_DECLARATION( ER_SYMBOL_EMBEDDED_NAME( logPointFormatterVDefault ) );	
	LOGPOINTS_EXPORT_EMBEDDED LOGPOINT_FORMATTER_DECLARATION( ER_SYMBOL_EMBEDDED_NAME( logPointFormat ) );
	LOGPOINTS_EXPORT_EMBEDDED LOGPOINT_FORMATTERV ER_SYMBOL_EMBEDDED_NAME( logPointGetFormatterV )(void);
	LOGPOINTS_EXPORT_EMBEDDED LOGPOINT_FORMATTERV ER_SYMBOL_EMBEDDED_NAME( logPointSetFormatterV )(LOGPOINT_FORMATTERV newFormatter);
#endif

LOGPOINTS_EXPORT_EMBEDDED const char *logPointGetLogFormat(void) ER_SYMBOL_WEAK_IMPORT;
LOGPOINTS_EXPORT_EMBEDDED const char *logPointSetLogFormat(const char * newFormat) ER_SYMBOL_WEAK_IMPORT;

#ifdef ER_EMBEDDED_NAME
LOGPOINTS_EXPORT_EMBEDDED const char * ER_SYMBOL_EMBEDDED_NAME( logPointGetLogFormat )(void);
LOGPOINTS_EXPORT_EMBEDDED const char * ER_SYMBOL_EMBEDDED_NAME( logPointSetLogFormat )(const char * newFormat);
#endif
	

#if __OBJC__

/* TESTING NSValue *__cmnsv = [[NSValue alloc] initWithBytes: &__cmv objCType: type]; */ /* NSValue secretly supports 'D'... */

#define LOGPOINT_FORMAT_VALUE(v, label) ({ \
	__typeof__ (v) __erValueToFormat = (v) ; \
	id (*__erValueFormatter)(const char *, void *, const char *) = ER_ADDRESS_OF_GLOBAL_OR_EMBEDDED( logPointFormatObjCType ); \
	const char *type = __builtin_types_compatible_p( __typeof__(__erValueToFormat), long double) ? "D" : @encode( __typeof__ (__erValueToFormat) ); \
	NULL == __erValueFormatter ? @"no_logPointFormatObjCType_weak_link_fail" : __erValueFormatter(type, (void*)&__erValueToFormat, (label)); /* returns autoreleased string */ \
}) 

/* 
 * internal helper function in logpoints.m, returns autoreleased string describing the @encode type at *data
 */ 
LOGPOINTS_EXPORT id logPointFormatObjCType(const char *type, void *data, const char *label) ER_SYMBOL_WEAK_IMPORT;
	
#ifdef ER_EMBEDDED_NAME
LOGPOINTS_EXPORT_EMBEDDED id ER_SYMBOL_EMBEDDED_NAME( logPointFormatObjCType )(const char *type, void *data, const char *label);
#endif

#endif
/* __OBJC__ */

#ifdef __cplusplus
}
#endif

#endif 
/* __LOGPOINTS_API_H__ */


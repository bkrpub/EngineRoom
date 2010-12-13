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

#include "logpoints_types.h"
#include "logpoints_private.h"
#include "logpoints_kinds.h"

#define LOGPOINTS_EXPORT /* __attribute__((visibility("default"))) */
#define LOGPOINTS_HIDDEN /* __attribute__((visibility("hidden"))) */
#define LOGPOINTS_WEAK   /* __attribute__((visibility("weak_import"))) */
#define LOGPOINTS_USED   /* __attribute__((visibility("used"))) */


#ifdef __cplusplus
extern "C" {
#endif


LOGPOINTS_EXPORT const char *logPointFileNameOnly(LOGPOINT *lpp);

/* error description from lp_return_t */
const char *logPointReturnString(lp_return_t err);

LOGPOINTS_EXPORT lp_return_t logPointReset(void);
LOGPOINTS_EXPORT lp_return_t logPointEnableSimple(const char *filter);
LOGPOINTS_EXPORT lp_return_t logPointDisableSimple(const char *filter);

LOGPOINTS_EXPORT lp_return_t logPointApplySimple(const char *filter, lp_uint_t options);

LOGPOINTS_EXPORT lp_return_t logPointDumpAll(void);

LOGPOINTS_EXPORT lp_return_t logPointActionDump(LOGPOINT *lp, void *actionInfo);

LOGPOINTS_EXPORT int         logPointFilterSimple(LOGPOINT *lp, void *filterInfo);

LOGPOINTS_EXPORT lp_return_t logPointApply(
			       LOGPOINT_FILTER filter, 
			       void *filterInfo,
			       LOGPOINT_WORKER action, 
			       void *actionInfo,
			       lp_uint_t options
			       );


LOGPOINTS_EXPORT const char *logPointPriorityNameFromNumber(int priority);
LOGPOINTS_EXPORT int logPointPriorityNumberFromName(const char *name);



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

/*
 * this is the first function invoked by a logpoint, full control, all responsibilities yours
 * if you don't care about ObjC, you can assume that "fmt" is const char *, otherwise it is
 * LOGPOINT_FLAG(*lpp, LOGPOINT_NSSTRING) ? CFStringRef : const char *
 */
typedef lp_return_t (*LOGPOINT_INVOKER)(LOGPOINT *lpp, const void *langspec1, const void *langspec2, const void *fmt, ...);
#define LOGPOINT_INVOKER_DECLARATION(name) lp_return_t name(LOGPOINT *lpp, const void *langspec1, const void *langspec2, const void *fmt, ...)

LOGPOINTS_EXPORT LOGPOINT_INVOKER_DECLARATION(logPointInvokerDefault);
LOGPOINTS_EXPORT LOGPOINTS_WEAK LOGPOINT_INVOKER logPointGetInvoker(void);
LOGPOINTS_EXPORT LOGPOINT_INVOKER logPointSetInvoker(LOGPOINT_INVOKER newInvoker);


/*
 * payload is the result of the users "fmt", ... arguments
 * if the ObjC version (logpoints.m) is used, payload is a CFStringRef, otherwise a const char *
 */
typedef lp_return_t (*LOGPOINT_COMPOSER)(LOGPOINT *lpp, const void *langspec1, const void *langspec2, LOGPOINT_MESSAGE_TYPE payload);

#define LOGPOINT_COMPOSER_DECLARATION(name) lp_return_t name(LOGPOINT *lpp, const void *langspec1, const void *langspec2, LOGPOINT_MESSAGE_TYPE payload)

LOGPOINTS_EXPORT LOGPOINT_COMPOSER_DECLARATION(logPointComposerDefault);
LOGPOINTS_EXPORT LOGPOINT_COMPOSER logPointGetComposer(void);
LOGPOINTS_EXPORT LOGPOINT_COMPOSER logPointSetComposer(LOGPOINT_COMPOSER newComposer);

/*
 * the composer will call the emitter with a format string and arguments decorating
 * the message produced by the invoker with metadata like location in source etc.
 */
typedef lp_return_t (*LOGPOINT_EMITTER)(LOGPOINT *lpp, const void *langspec1, const void *langspec2, const char *fmt, ...);

#define LOGPOINT_EMITTER_DECLARATION(name) lp_return_t name(LOGPOINT *lpp, const void *langspec1, const void *langspec2, const char *fmt, ...)

LOGPOINTS_EXPORT LOGPOINT_EMITTER_DECLARATION(logPointEmitterDefault);
LOGPOINTS_EXPORT LOGPOINT_EMITTER logPointGetEmitter(void);
LOGPOINTS_EXPORT LOGPOINT_EMITTER logPointSetEmitter(LOGPOINT_EMITTER newEmitter);




#if __OBJC__

/* TESTING NSValue *__cmnsv = [[NSValue alloc] initWithBytes: &__cmv objCType: type]; */ /* NSValue secretly supports 'D'... */

#ifdef LOCAL_CLIENT
#define LOGPOINT_FORMAT_VALUE(v, label) ({ \
	__typeof__ (v) __valueToFormat = (v) ; \
	char *type = __builtin_types_compatible_p( __typeof__(__valueToFormat), long double) ? "D" : @encode( __typeof__ (__valueToFormat) ); \
	(logPointFormatObjCType ? logPointFormatObjCType : local_logPointFormatObjCType)(type, (void*)&__valueToFormat, (label)); /* returns autoreleased string */ \
}) 
#else
#define LOGPOINT_FORMAT_VALUE(v, label) ({ \
	__typeof__ (v) __valueToFormat = (v) ; \
	char *type = __builtin_types_compatible_p( __typeof__(__valueToFormat), long double) ? "D" : @encode( __typeof__ (__valueToFormat) ); \
	(logPointFormatObjCType)(type, (void*)&__valueToFormat, (label)); /* returns autoreleased string */ \
}) 
#endif

/* 
 * internal helper function in logpoints.m, returns autoreleased string describing the @encode type at *data
 */ 
LOGPOINTS_EXPORT LOGPOINTS_WEAK id logPointFormatObjCType(const char *type, void *data, const char *label);

#endif

#if LOCAL_CLIENT
static LOGPOINTS_HIDDEN LOGPOINTS_USED LOGPOINT_INVOKER_DECLARATION(local_logPointInvokerDefault)
{
#ifdef MAINTAINER_WARNINGS
#warning local client test
#warning no non-objc support
#endif  

	va_list args;
	va_start(args, fmt);
	
	NSString *msg = nil;

	if( nil != fmt ) {
	  NSString *nsfmt = LOGPOINT_IS_NSSTRING(*lpp) ? (id)fmt : [[NSString alloc] initWithUTF8String: (const char *)fmt];

	  msg = [[NSString alloc] initWithFormat: nsfmt arguments: args];

	  if( LOGPOINT_IS_NSSTRING(*lpp) ) {
	    [nsfmt release];
	  }
	}

	NSLog(@"localInvoker: %s %@", lpp->kind, msg ?: @"NO PAYLOAD");
	[msg release];

	va_end(args);
	return LOGPOINT_YES;
}

/* ObjC ! */
#import "CrossPlatform_NSString_CGGeometry.h"

static LOGPOINTS_HIDDEN LOGPOINTS_USED id local_logPointFormatObjCType(const char *type, void *data, const char *label) 
{
	if( NULL == type ) 
		return @"NILTYPE";

	id ret = nil;

	if('r' == *type) { // const
		++type;
	}

	void *ptr = *(void **) data;
		
	
	switch( *type ) {
		case '@':
			ret = ptr ? [(id) ptr description] : @"nil"; break;
					
		case '#':
			ret = ptr ? [(id) ptr description] : @"Nil"; break;

		case '*': ret = [NSString stringWithFormat: @"char*: '%s'", *(char **)data]; break;

		case 'c': ret = [NSString stringWithFormat: @"char: 0x%02hhx", *(char *)data]; break;
		case 'C': ret = [NSString stringWithFormat: @"uchar: 0x%02hhx", *(unsigned char *)data]; break;
		case 's': ret = [NSString stringWithFormat: @"short: 0x%02hx", *(short *)data]; break;
		case 'S': ret = [NSString stringWithFormat: @"ushort: 0x%02hx", *(unsigned short *)data]; break;
		case 'i': ret = [NSString stringWithFormat: @"int: 0x%02x", *(int *)data]; break;
		case 'I': ret = [NSString stringWithFormat: @"uint: 0x%02x", *(unsigned int *)data]; break;
		case 'l': ret = [NSString stringWithFormat: @"long: 0x%02lx", *(long *)data]; break;
		case 'L': ret = [NSString stringWithFormat: @"ulong: 0x%02lx", *(unsigned long *)data]; break;
		case 'q': ret = [NSString stringWithFormat: @"quad: 0x%02llx", *(long long *)data]; break;
		case 'Q': ret = [NSString stringWithFormat: @"uquad: 0x%02llx", *(unsigned long long *)data]; break;
		case 'f': ret = [NSString stringWithFormat: @"float: %.*g", __FLT_DIG__, *(float *)data]; break;
		case 'd': ret = [NSString stringWithFormat: @"double: %.*lg", __DBL_DIG__, *(double *)data]; break;

		/* warning: not officially supported - not generated by @encode but works in NSValue */
		case 'D': ret = [NSString stringWithFormat: @"double: %.*Lg", __LDBL_DIG__, *(long double *)data]; break;

		case ':': ret = NSStringFromSelector(*(SEL*)data); break;

		case '{': 
			if( 0 == strncmp(type+1, "_NSRange=", 9) ) {
				ret = NSStringFromRange( *(NSRange *) data);
#if TARGET_OS_OSX
			} else if( 0 == strncmp(type+1, "_NSPoint=", 9) ) {
				ret = NSStringFromPoint( *(NSPoint *) data);
			} else if( 0 == strncmp(type+1, "_NSSize=", 8) ) {
				ret = NSStringFromSize( *(NSSize *) data);
			} else if( 0 == strncmp(type+1, "_NSRect=", 8) ) {
				ret = NSStringFromRect( *(NSRect *) data);
#endif
			} else if( 0 == strncmp(type+1, "CGPoint=", 8) ) {
				ret = NSStringFromCGPoint( *(CGPoint *) data);
			} else if( 0 == strncmp(type+1, "CGSize=", 7) ) {
				ret = NSStringFromCGSize( *(CGSize *) data);
			} else if( 0 == strncmp(type+1, "CGRect=", 7) ) {
				ret = NSStringFromCGRect( *(CGRect *) data);
			} else {
				ret = [NSString stringWithFormat: @"struct(%s)", type]; break;
			}
			break;


		case '[': ret = [NSString stringWithFormat: @"array(%s)", type]; break;

		case '^': 

			if( 0 == strncmp(type+1, "{__CF", 5)) {
				if(	0 == strncmp(type+6, "String=", 7) || 0 == strncmp(type+6, "Number=", 7) ) {
					ret = [(id) ptr description];
				} else {

					ret = UTIL_AUTORELEASE_CF_AS_ID( CFCopyDescription( (CFTypeRef) ptr) );			
				}
			} else {
				switch( type[1] ) {
				
					case '{': ret = [NSString stringWithFormat: @"struct*(%s): %p", type, ptr]; break;
					case '?': ret = [NSString stringWithFormat: @"func*: %p", ptr]; break;
					case '^': ret = [NSString stringWithFormat: @"ptr*: %p", ptr]; break;
					case '*': ret = [NSString stringWithFormat: @"char**: %p", ptr]; break;
					case 'v': ret = [NSString stringWithFormat: @"void*: %p", ptr]; break;

					case 'B': 
					case 'c': 
					case 'C': 
					case 's': 
					case 'S': 
					case 'i': 
					case 'I': 
					case 'l': 
					case 'L': 
					case 'q': 
					case 'Q': 
					case 'f': 
					case 'd': 
					case 'D': /* won't be seen - no special case code - so it is ^d */
					case '@': 
					case '#': 
					case ':': 
						ret = [NSString stringWithFormat: @"basic(%c)*: %p", type[1], ptr]; break;

					default:
						ret = [NSString stringWithFormat: @"other(%c)*: %p", type[1], ptr]; break;
				}
			}
			break;

		case 'B': ret = @"C++ Bool or C99 _Bool - still unsupported"; break;
		case 'b': ret = @"bitfield - still unsupported"; break;

		case '?': ret = @"unknown type (?)"; break;
		
		default:
			ret = [NSString stringWithFormat: @"unknown type character '%c'", *type];
			break;
	}
		
	return [NSString stringWithFormat: @"%s%s%@", 
		label && *label ? label : "",
		label && *label ? ": " : "",
		ret ? ret : [NSString stringWithFormat: @"type not decoded (%s)", type]];

}

#endif
/* LOCAL_CLIENT */



#ifdef __cplusplus
}
#endif

#endif 
/* __LOGPOINTS_API_H__ */


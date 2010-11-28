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


/* error description from lp_return_t */
const char *logPointFileNameOnly(LOGPOINT *lpp);

const char *logPointReturnString(lp_return_t err);

lp_return_t logPointReset(void);
lp_return_t logPointEnableSimple(const char *filter);
lp_return_t logPointDisableSimple(const char *filter);

lp_return_t logPointApplySimple(const char *filter, lp_uint_t options);

lp_return_t logPointDumpAll(void);

lp_return_t logPointActionDump(LOGPOINT *lp, void *actionInfo);

int         logPointFilterSimple(LOGPOINT *lp, void *filterInfo);

lp_return_t logPointApply(
			       LOGPOINT_FILTER filter, 
			       void *filterInfo,
			       LOGPOINT_WORKER action, 
			       void *actionInfo,
			       lp_uint_t options
			       );


const char *logPointPriorityNameFromNumber(int priority);
int logPointPriorityNumberFromName(const char *name);



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

#warning local client test
static lp_return_t __attribute__((used)) local_logPointInvokerDefault (LOGPOINT *lpp, const void *langspec1, const void *langspec2, const void *fmt, ...) 
{
#warning nsstring / cstring
	va_list args;
	va_start(args, fmt);
	NSString *nsfmt = [[NSString alloc] initWithUTF8String: fmt];
	NSString *msg = [[NSString alloc] initWithFormat: nsfmt arguments: args];
	NSLog(@"localInvoker: %@", msg);
	[msg release];
	[nsfmt release];
	va_end(args);
	return 0;
}

/* ObjC ! */
#import "CrossPlatform_NSString_CGGeometry.h"

static id __attribute__((used)) local_logPointFormatObjCType(const char *type, void *data, const char *label) 
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

extern LOGPOINT_INVOKER_DECLARATION(logPointInvokerDefault);
#warning weak test
LOGPOINT_INVOKER logPointGetInvoker(void) __attribute__((weak_import)); 
LOGPOINT_INVOKER logPointSetInvoker(LOGPOINT_INVOKER newInvoker);


/*
 * payload is the result of the users "fmt", ... arguments
 * if the ObjC version (logpoints.m) is used, payload is a CFStringRef, otherwise a const char *
 */
typedef lp_return_t (*LOGPOINT_COMPOSER)(LOGPOINT *lpp, const void *langspec1, const void *langspec2, LOGPOINT_MESSAGE_TYPE payload);

#define LOGPOINT_COMPOSER_DECLARATION(name) lp_return_t name(LOGPOINT *lpp, const void *langspec1, const void *langspec2, LOGPOINT_MESSAGE_TYPE payload)

extern LOGPOINT_COMPOSER_DECLARATION(logPointComposerDefault);
LOGPOINT_COMPOSER logPointGetComposer(void);
LOGPOINT_COMPOSER logPointSetComposer(LOGPOINT_COMPOSER newComposer);

/*
 * the composer will call the emitter with a format string and arguments decorating
 * the message produced by the invoker with metadata like location in source etc.
 */
typedef lp_return_t (*LOGPOINT_EMITTER)(LOGPOINT *lpp, const void *langspec1, const void *langspec2, const char *fmt, ...);

#define LOGPOINT_EMITTER_DECLARATION(name) lp_return_t name(LOGPOINT *lpp, const void *langspec1, const void *langspec2, const char *fmt, ...)

extern LOGPOINT_EMITTER_DECLARATION(logPointEmitterDefault);
LOGPOINT_EMITTER logPointGetEmitter(void);
LOGPOINT_EMITTER logPointSetEmitter(LOGPOINT_EMITTER newEmitter);


#if __OBJC__

/* TESTING NSValue *__cmnsv = [[NSValue alloc] initWithBytes: &__cmv objCType: type]; */ /* NSValue secretly supports 'D'... */

#define LOGPOINT_FORMAT_VALUE(v, label) ({ \
	__typeof__ (v) __valueToFormat = (v) ; \
	char *type = __builtin_types_compatible_p( __typeof__(__valueToFormat), long double) ? "D" : @encode( __typeof__ (__valueToFormat) ); \
	(logPointFormatObjCType ? logPointFormatObjCType : local_logPointFormatObjCType)(type, (void*)&__valueToFormat, (label)); /* returns autoreleased string */ \
}) 

/* 
 * internal helper function in logpoints.m, returns autoreleased string describing the @encode type at *data
 */ 
id logPointFormatObjCType(const char *type, void *data, const char *label) __attribute__((weak_import));

#endif

#endif 
/* __LOGPOINTS_API_H__ */


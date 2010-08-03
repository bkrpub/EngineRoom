/*
 *  $Id: logpoints_api.h 762 2009-02-21 23:56:12Z bkr $
 *
 *  Copyright (c) 2007 Bjoern Kriews
 */

#ifndef __LOGPOINTS_API_H__
#define __LOGPOINTS_API_H__ 1

#include "logpoints_types.h"
#include "logpoints_private.h"

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

/* override this with your own -D if you need to */
#ifndef LOGPOINT_INVOKE
#define LOGPOINT_INVOKE(lpp, langspec1, langspec2, fmt, ...) (*logPointGetInvoker())((lpp), (langspec1), (langspec2), (fmt), ## __VA_ARGS__ )
#endif

/*
 * all code that uses or declares these types must be compiled in the same language
 */
#ifdef __OBJC__
typedef CFStringRef LOGPOINT_MESSAGE_TYPE;
#define LOGPOINT_MESSAGE_FORMAT "%@"
#else
typedef char *LOGPOINT_MESSAGE_TYPE;
#define LOGPOINT_MESSAGE_FORMAT "%s"
#endif

/*
 * this is the first function invoked by a logpoint, full control, all responsibilities yours
 * if you don't care about ObjC, you can assume that "fmt" is const char *, otherwise it is
 * LOGPOINT_FLAG(*lpp, LOGPOINT_NSSTRING) ? CFStringRef : const char *
 */
typedef lp_return_t (*LOGPOINT_INVOKER)(LOGPOINT *lpp, const void *langspec1, const void *langspec2, const void *fmt, ...);
#define LOGPOINT_INVOKER_DECLARATION(name) lp_return_t name(LOGPOINT *lpp, const void *langspec1, const void *langspec2, const void *fmt, ...)

extern LOGPOINT_INVOKER_DECLARATION(logPointInvokerDefault);
LOGPOINT_INVOKER logPointGetInvoker(void); 
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

#define LOGPOINT_FORMAT_VALUE(v, label) ({ \
	__typeof__ (v) __cmv = (v) ; \
	char *type = __builtin_types_compatible_p( __typeof__(__cmv), long double) ? "D" : @encode( __typeof__ (__cmv) ); \
	/* TESTING NSValue *__cmnsv = [[NSValue alloc] initWithBytes: &__cmv objCType: type]; */ /* NSValue secretly supports 'D'... */ \
	logPointFormatObjCType(type, (void*)&__cmv, label); /* returns autoreleased string */ \
}) 

/* 
 * internal helper function in logpoints.m, returns autoreleased string describing the @encode type at *data
 */ 
id logPointFormatObjCType(const char *type, void *data, const char *label);

#endif

#endif 
/* __LOGPOINTS_API_H__ */


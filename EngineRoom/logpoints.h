/*
 *  $Id: logpoints.h 711 2008-03-08 10:22:12Z bkr $
 *
 *  Copyright (c) 2007 Bjoern Kriews
 */

#ifndef __LOGPOINTS_H__
#define __LOGPOINTS_H__

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import <objc/runtime.h>
#endif

#include "logpoints_api.h"

/*
 * 
 * this file declares the macros used to create logpoints in code 
 * these are an "interface layer" to the guts of the logpoint code,
 * you should use these to define a frontend for your usage
 */

/* C String Versions */

/*
 * for generic use in any part of a C, C++, ObjC or ObjC++ source file
 */
#define LOGPOINT_FUNCTION_C(flags, kind, keys, label, fmt, ...)           LOGPOINT_CREATE( (flags) | LOGPOINT_C, (kind), (keys), (label), NULL, NULL, fmt, ## __VA_ARGS__ )

/*
 * only for use in Objective C methods in ObjC or ObjC++ source files, forwards "self" and "_cmd" to the logpoint invocation
 */
#define LOGPOINT_METHOD_OBJC(flags, kind, keys, label, fmt, ...)          LOGPOINT_CREATE( (flags) | LOGPOINT_OBJC, (kind), (keys), (label), self, _cmd, fmt, ## __VA_ARGS__ )

/* 
 * only for use in C++ methods in ObjC or ObjC++ source files, forwards "this" to the logpoint invocation
 */
#define LOGPOINT_METHOD_CXX(flags, kind, keys, label, fmt, ...)           LOGPOINT_CREATE( (flags) | LOGPOINT_CXX, (kind), (keys), (label), this, NULL, fmt, ## __VA_ARGS__ )


#ifdef __OBJC__

/* NSString versions - I have not yet decided if these will stay - these accept an NS/CFString for the format argument */ 

/*
 * for use in any part of a C, C++, ObjC or ObjC++ source file 
 */
#define LOGPOINT_FUNCTION_C_NS(flags, kind, keys, label, fmt, ...)        LOGPOINT_FUNCTION_C( (flags) | LOGPOINT_NSSTRING, (kind), (keys), (label), fmt, ## __VA_ARGS__ )

/*
 * only for use in Objective C methods in ObjC or ObjC++ source files, forwards "self" and "_cmd" to the logpoint invocation
 */
#define LOGPOINT_METHOD_OBJC_NS(flags, kind, keys, label, fmt, ...)       LOGPOINT_METHOD_OBJC( (flags) | LOGPOINT_NSSTRING, (kind), (keys), (label), fmt, ## __VA_ARGS__ )

/* 
 * only for use in C++ methods in ObjC or ObjC++ source files, forwards "this" to the logpoint invocation 
 */
#define LOGPOINT_METHOD_CXX_NS(flags, kind, keys, label, fmt, ...)        LOGPOINT_METHOD_CXX( (flags) | LOGPOINT_NSSTRING, (kind), (keys), (label), fmt, ## __VA_ARGS__ )

#endif 
/* __OBJC__ */

/* the following constants must be declared as char[] to be used in static initializers */

/* syslog equivalents */
LOGPOINT_EXTERN_C(kLogPointKindDebug[],     const char, "DEBUG");
LOGPOINT_EXTERN_C(kLogPointKindInfo[],      const char, "INFO");
LOGPOINT_EXTERN_C(kLogPointKindNotice[],    const char, "NOTICE");
LOGPOINT_EXTERN_C(kLogPointKindWarning[],   const char, "WARNING");
LOGPOINT_EXTERN_C(kLogPointKindError[],     const char, "ERROR");
LOGPOINT_EXTERN_C(kLogPointKindCritical[],  const char, "CRITICAL");
LOGPOINT_EXTERN_C(kLogPointKindAlert[],     const char, "ALERT");
LOGPOINT_EXTERN_C(kLogPointKindEmergency[], const char, "EMERGENCY");

LOGPOINT_EXTERN_C(kLogPointKindTrace[],     const char, "TRACE");

LOGPOINT_EXTERN_C(kLogPointKindNote[],      const char, "NOTE");
LOGPOINT_EXTERN_C(kLogPointKindFixMe[],     const char, "FIXME");
LOGPOINT_EXTERN_C(kLogPointKindToDo[],      const char, "TODO");

LOGPOINT_EXTERN_C(kLogPointKindSwitch[],    const char, "SWITCH");

LOGPOINT_EXTERN_C(kLogPointKindAssert[],    const char, "ASSERT");


LOGPOINT_EXTERN_C(kLogPointNoFormat,    const char* const, NULL);

#endif 
/* __LOGPOINTS_H__ */


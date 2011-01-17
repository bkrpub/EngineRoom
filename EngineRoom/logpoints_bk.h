/*
 * please ignore this file - it is here because it is still used by some transitional code
 */

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

#ifndef __LOGPOINTS_BK_H__
#define __LOGPOINTS_BK_H__ 1

#include "logpoints.h"
#include "logpoints_default_policy.h"

#ifdef __OBJC__
#define LPLog(fmt, ...) LOGPOINT_FUNCTION_C_NS( LOGPOINT_NOFLAGS, "NSLog", NULL, NULL, fmt, ## __VA_ARGS__ ) 

#define lp(fmt, ...)    LOGPOINT_FUNCTION_C( LOGPOINT_NOFLAGS, "lp", NULL, NULL, fmt, ## __VA_ARGS__ ) 

#define dbug(v)   ({ id __msg = LOGPOINT_FORMAT_VALUE(v, #v); int __ret = LOGPOINT_METHOD_OBJC( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, NULL, "", "%@", __msg ); __ret; }) 
#define dbug2(v1,v2)   ({ id __msg1 = LOGPOINT_FORMAT_VALUE(v1, #v1); id __msg2 = LOGPOINT_FORMAT_VALUE(v2, #v2); int __ret = LOGPOINT_METHOD_OBJC( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, NULL, "", "[%@] [%@]", __msg1, __msg2 ); __ret; }) 

#define dbugC(v)   ({ id __msg = LOGPOINT_FORMAT_VALUE(v, #v); int __ret = LOGPOINT_FUNCTION_C( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, NULL, "", "%@", __msg ); __ret; }) 

#define dbug_return(v) return ({ \
	__typeof__(v) __returnTmp = (v); \
	id __msg = LOGPOINT_FORMAT_VALUE(v, #v); \
	LOGPOINT_METHOD_OBJC( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, NULL, "", "return: %@", __msg ); \
	__returnTmp; })

#define dbug_returnC(v) return ({ \
	__typeof__(v) __returnTmp = (v); \
	id __msg = LOGPOINT_FORMAT_VALUE(v, #v); \
	LOGPOINT_FUNCTION_C( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, NULL, "", "return: %@", __msg ); \
	__returnTmp; })

#else

/* no non-objC dbug support right now */

#endif

/*
 * support for my own previous usage - bkr 
 */

#define lpSoftLogMessage(flags, kind, keys, langSpec1, langSpec2, fmt, ...) \
  _lpSoftLogMessage(#fmt ", " #__VA_ARGS__, (flags), (kind), (keys), (langSpec1), (langSpec2), fmt, ## __VA_ARGS__)

#define lpHardLogMessage(flags, kind, keys, langSpec1, langSpec2, fmt, ...) \
  _lpHardLogMessage(#fmt ", " #__VA_ARGS__, (flags), (kind), (keys), (langSpec1), (langSpec2), fmt, ## __VA_ARGS__)

#define _lpSoftLogMessage(label, flags, kind, keys, langSpec1, langSpec2, fmt, ...) \
  LOGPOINT_CREATE( (flags), (kind), (keys), (label), (langSpec1), (langSpec2), fmt, ## __VA_ARGS__)

#define _lpHardLogMessage(label, flags, kind, keys, langSpec1, langSpec2, fmt, ...) \
  LOGPOINT_CREATE( (flags) | LOGPOINT_ACTIVE | LOGPOINT_HARD, (kind), (keys), (label), (langSpec1), (langSpec2), fmt, ## __VA_ARGS__)


#if LOGPOINT_ENABLE_ASSERT
#define LPAssert(cond, desc)  ({ (cond) ? LOGPOINT_ZERO : LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, NULL, #cond, "%@", desc); })
#define LPCAssert(cond, desc) ({ (cond) ? LOGPOINT_ZERO :  LOGPOINT_FUNCTION_C(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, NULL, #cond, "%@", desc); })
#define LPAssertF(cond, fmt, ...)  ({ (cond) ? LOGPOINT_ZERO : LOGPOINT_METHOD_OBJC_NS(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, NULL, #cond, fmt, ## __VA_ARGS__); })
#define LPCAssertF(cond, fmt, ...) ({ (cond) ? LOGPOINT_ZERO :  LOGPOINT_FUNCTION_C_NS(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, NULL, #cond, fmt, ## __VA_ARGS__); })
#define LPParameterAssert(cond)   ({ (cond) ? LOGPOINT_ZERO : LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, NULL, #cond, kLogPointNoFormat); })
#define LPCParameterAssert(cond)  ({ (cond) ? LOGPOINT_ZERO :  LOGPOINT_FUNCTION_C(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, NULL, #cond, kLogPointNoFormat); })
#else
#define LPAssert(cond, desc)               LOGPOINT_ZERO
#define LPCAssert(cond, desc)              LOGPOINT_ZERO
#define LPAssertF(cond, fmt, ...)          LOGPOINT_ZERO
#define LPCAssertF(cond, fmt, ...)         LOGPOINT_ZERO
#define LPParameterAssert(cond, fmt, ...)  LOGPOINT_ZERO
#define LPParameterCAssert(cond, fmt, ...) LOGPOINT_ZERO
#endif

#define lperror(keys, fmt, ...)   LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_ERROR, kLogPointKindError, keys, NULL, fmt, ## __VA_ARGS__)
#define lpcerror(keys, fmt, ...)   LOGPOINT_FUNCTION_C(LOGPOINT_FLAGS_ERROR, kLogPointKindError, keys, NULL, fmt, ## __VA_ARGS__)

#if LOGPOINT_ENABLE_WARNING
#define lpwarning(keys, fmt, ...)   LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, keys, NULL, fmt, ## __VA_ARGS__)
#define lpcwarning(keys, fmt, ...)  LOGPOINT_FUNCTION_C(LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, keys, NULL, fmt, ## __VA_ARGS__)
#else
#define lpwarning(keys, fmt, ...)   LOGPOINT_ZERO
#define lpcwarning(keys, fmt, ...)  LOGPOINT_ZERO
#endif
      

#if LOGPOINT_ENABLE_TRACE
#define LPTRACE                     LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, NULL, NULL, kLogPointNoFormat)
#define LPMEMTRACE                  LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, NULL, NULL, kLogPointNoFormat)

#define lptrace(keys)               _lpSoftLogMessage("", 0, "TRACE", keys, self, _cmd, "")
#define lpctrace(keys)              _lpSoftLogMessage("", 0, "TRACE", keys, NULL, NULL, "")
#else
#define LPTRACE                     LOGPOINT_ZERO
#define LPMEMTRACE                  LOGPOINT_ZERO
#define lptrace(keys, ...)          LOGPOINT_ZERO
#define lpctrace(keys, ...)         LOGPOINT_ZERO
#endif

#if LOGPOINT_ENABLE_DEBUG
#define lpdebug(keys, fmt, ...)     LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, keys, NULL, fmt, ## __VA_ARGS__)
#define lpcdebug(keys, fmt, ...)     LOGPOINT_FUNCTION_C(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, keys, NULL, fmt, ## __VA_ARGS__)

#define lpsingle(keys, label, fmt, value)  LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, keys, label " =", fmt, value)
#define lpcsingle(keys, label, fmt, value)  LOGPOINT_FUNCTION_C(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, keys, label " =", fmt, value)

#define lpdebug1(keys, value)       lpsingle(keys, #value, "%@", value)
#define lpcdebug1(keys, value)      lpcsingle(keys, #value, "%@", value)
//#define lpdebug1(keys, value)       LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, keys, NULL, "%s = %@", #value, value)
//#define lpcdebug1(keys, value)       LOGPOINT_FUNCTION_C(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, keys, NULL, "%s = %@", #value, value)

#define lpInt(keys, value)          lpsingle(keys, #value, "%d", (int) value)
#define lpcInt(keys, value)         lpcsingle(keys, #value, "%d", (int) value)
//#define lpInt(keys, value)          _lpSoftLogMessage(#value, LOGPOINT_OBJC, "DEBUG", keys, self, _cmd, "%s = %d", #value, value)
//#define lpcInt(keys, value)          _lpSoftLogMessage(#value, LOGPOINT_C, "DEBUG", keys, NULL, NULL, "%s = %d", #value, value)

#define lpDouble(keys, value)       _lpSoftLogMessage(#value, LOGPOINT_OBJC, "DEBUG", keys, self, _cmd, "%s = %f", #value, value)
#define lpcDouble(keys, value)       _lpSoftLogMessage(#value, LOGPOINT_C, "DEBUG", keys, NULL, NULL, "%s = %f", #value, value)

#define lpRect(keys, value)         _lpSoftLogMessage("NSRect: " #value, LOGPOINT_OBJC, "DEBUG", keys, self, _cmd, "%s = %@", #value, NSStringFromRect(value))
#define lpcRect(keys, value)         _lpSoftLogMessage("NSRect: " #value, LOGPOINT_C, "DEBUG", keys, NULL, NULL, "%s = %@", #value, NSStringFromRect(value))

#define lpPoint(keys, value)        _lpSoftLogMessage("NSPoint: " #value, LOGPOINT_OBJC, "DEBUG", keys, self, _cmd, "%s = %@", #value, NSStringFromPoint(value))
#define lpcPoint(keys, value)        _lpSoftLogMessage("NSPoint: " #value, LOGPOINT_C, "DEBUG", keys, NULL, NULL, "%s = %@", #value, NSStringFromPoint(value))

#define lpSize(keys, value)         _lpSoftLogMessage("NSSize: " #value, LOGPOINT_OBJC, "DEBUG", keys, self, _cmd, "%s = %@", #value, NSStringFromSize(value))
#define lpcSize(keys, value)         _lpSoftLogMessage("NSSize: " #value, LOGPOINT_C, "DEBUG", keys, NULL, NULL, "%s = %@", #value, NSStringFromSize(value))

#define lpRange(keys, value)        _lpSoftLogMessage("NSRange: " #value, LOGPOINT_OBJC, "DEBUG", keys, self, _cmd, "%s = %@", #value, NSStringFromRange(value))
#define lpcRange(keys, value)        _lpSoftLogMessage("NSRange: " #value, LOGPOINT_C, "DEBUG", keys, NULL, NULL, "%s = %@", #value, NSStringFromRange(value))

#define lpshow(value)               _lpSoftLogMessage(#value, LOGPOINT_OBJC, "DEBUG", #value, self, _cmd, "%@", value)
#define lpcshow(value)               _lpSoftLogMessage(#value, LOGPOINT_C, "DEBUG", #value, NULL, NULL, "%@", value)

#else

#define lpdebug(keys, ...)          LOGPOINT_ZERO
#define lpcdebug(keys, ...)         LOGPOINT_ZERO

#define lpdebug1(keys, ...)         LOGPOINT_ZERO
#define lpcdebug1(keys, ...)        LOGPOINT_ZERO

#define lpInt(keys, ...)            LOGPOINT_ZERO
#define lpcInt(keys, ...)           LOGPOINT_ZERO

#define lpDouble(keys, ...)         LOGPOINT_ZERO
#define lpcDouble(keys, ...)        LOGPOINT_ZERO

#define lpRect(keys, v)             LOGPOINT_ZERO
#define lpcRect(keys, v)            LOGPOINT_ZERO

#define lpPoint(keys, v)            LOGPOINT_ZERO
#define lpcPoint(keys, v)           LOGPOINT_ZERO

#define lpSize(keys, v)             LOGPOINT_ZERO
#define lpcSize(keys, v)            LOGPOINT_ZERO

#define lpRange(keys, v)            LOGPOINT_ZERO
#define lpcRange(keys, v)           LOGPOINT_ZERO

#define lpshow(v)		    LOGPOINT_ZERO
#define lpcshow(v)		    LOGPOINT_ZERO

#endif

#if LOGPOINT_ENABLE_NOTES
#define lpFIXME(fmt, ...)           lpHardLogMessage(LOGPOINT_OBJC, "FIXME", NULL, self, _cmd, fmt, ## __VA_ARGS__)
#define lpcFIXME(fmt, ...)           lpHardLogMessage(LOGPOINT_C, "FIXME", NULL, NULL, NULL, fmt, ## __VA_ARGS__)
#define lpTODO(fmt, ...)            lpHardLogMessage(LOGPOINT_OBJC, "TODO", NULL, self, _cmd, fmt, ## __VA_ARGS__)
#define lpcTODO(fmt, ...)            lpHardLogMessage(LOGPOINT_C, "TODO", NULL, NULL, NULL, fmt, ## __VA_ARGS__)
#else
#define lpFIXME(fmt, ...)           LOGPOINT_ZERO
#define lpcFIXME(fmt, ...)          LOGPOINT_ZERO
#define lpTODO(fmt, ...)            LOGPOINT_ZERO
#define lpcTODO(fmt, ...)           LOGPOINT_ZERO
#endif

#if LOGPOINT_ENABLE_SWITCH

/* Usage: if( lpswitch("key1,key2", fmt) ) { ... */

#define lpswitch(keys, fmt, ...)     LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_SWITCH, kLogPointKindSwitch, keys, NULL, fmt, ## __VA_ARGS__)
#define lpcswitch(keys, fmt, ...)     LOGPOINT_FUNCTION_C(LOGPOINT_FLAGS_SWITCH, kLogPointKindSwitch, keys, NULL, fmt, ## __VA_ARGS__)
#define lpdebugswitch(keys, fmt, ...)     LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_DEBUG_SWITCH, kLogPointKindSwitch, keys, NULL, fmt, ## __VA_ARGS__)
#define lpcdebugswitch(keys, fmt, ...)     LOGPOINT_FUNCTION_C(LOGPOINT_FLAGS_DEBUG_SWITCH, kLogPointKindSwitch, keys, NULL, fmt, ## __VA_ARGS__)
#else
#define lpswitch(keys, fmt, ...)     0
#define lpcswitch(keys, fmt, ...)    0
#define lpdebugswitch(keys, fmt, ...)     0
#define lpcdebugswitch(keys, fmt, ...)    0
#endif


#define LPABSTRACT                  LPASSERT(NULL, @"needs implementation in subclass")


#endif
/* __LOGPOINTS_BK_H__ */

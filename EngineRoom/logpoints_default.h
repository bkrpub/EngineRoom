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

#ifndef __LOGPOINTS_DEFAULT_H__
#define __LOGPOINTS_DEFAULT_H__ 1

/* make sure to include the policy first (for ENABLE defines/overrides to work) */
#include "logpoints_default_policy.h"
#include "logpoints.h"

#ifdef __OBJC__

/* used by logpoints_nslog.h to replace NSLog */
#define lpNSLog(fmt, ...) LOGPOINT_FUNCTION_C_NS( LOGPOINT_NOFLAGS, "NSLog", kLogPointKeysNone, kLogPointLabelNone, fmt, ## __VA_ARGS__ ) 
/* (?) lpNSLogv */

#endif
/* __OBJC__ */

/* (?) enabled ?
#define lplog(fmt, ...)    LOGPOINT_FUNCTION_C( LOGPOINT_NOFLAGS, "lplog", kLogPointKeysNone, kLogPointLabelNone, fmt, ## __VA_ARGS__ ) 
*/


#if LOGPOINT_ENABLE_ASSERT
#define lpassert(cond, desc)  ({ (cond) ? LOGPOINT_EMPTY : LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, kLogPointKeysNone, #cond, "%@", desc); })
#define lpcassert(cond, desc)  ({ (cond) ? LOGPOINT_EMPTY : LOGPOINT_FUNCTION_C(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, kLogPointKeysNone, #cond, "%@", desc); })

#define LPAssert(cond, desc)  ({ (cond) ? LOGPOINT_EMPTY : LOGPOINT_METHOD_OBJC_NS(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, kLogPointKeysNone, #cond, "%@", desc); })
#define LPCAssert(cond, desc) ({ (cond) ? LOGPOINT_EMPTY :  LOGPOINT_FUNCTION_C_NS(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, kLogPointKeysNone, #cond, "%@", desc); })
#define LPAssertF(cond, fmt, ...)  ({ (cond) ? LOGPOINT_EMPTY : LOGPOINT_METHOD_OBJC_NS(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, kLogPointKeysNone, #cond, fmt, ## __VA_ARGS__); })
#define LPCAssertF(cond, fmt, ...) ({ (cond) ? LOGPOINT_EMPTY :  LOGPOINT_FUNCTION_C_NS(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, kLogPointKeysNone, #cond, fmt, ## __VA_ARGS__); })
#define LPParameterAssert(cond)   ({ (cond) ? LOGPOINT_EMPTY : LOGPOINT_METHOD_OBJC_NS(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, kLogPointKeysNone, #cond, kLogPointFormatNone); })
#define LPCParameterAssert(cond)  ({ (cond) ? LOGPOINT_EMPTY :  LOGPOINT_FUNCTION_C(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, kLogPointKeysNone, #cond, kLogPointFormatNone); })
#else
#define LPAssert(cond, desc)               LOGPOINT_EMPTY
#define LPCAssert(cond, desc)              LOGPOINT_EMPTY
#define LPAssertF(cond, fmt, ...)          LOGPOINT_EMPTY
#define LPCAssertF(cond, fmt, ...)         LOGPOINT_EMPTY
#define LPParameterAssert(cond, fmt, ...)  LOGPOINT_EMPTY
#define LPParameterCAssert(cond, fmt, ...) LOGPOINT_EMPTY
#endif

#define lperror(keys, fmt, ...)   LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_ERROR, kLogPointKindError, keys, kLogPointLabelNone, fmt, ## __VA_ARGS__)
#define lpcerror(keys, fmt, ...)   LOGPOINT_FUNCTION_C(LOGPOINT_FLAGS_ERROR, kLogPointKindError, keys, kLogPointLabelNone, fmt, ## __VA_ARGS__)

#if LOGPOINT_ENABLE_WARNING
#define lpwarning(keys, fmt, ...)   LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, keys, kLogPointLabelNone, fmt, ## __VA_ARGS__)
#define lpcwarning(keys, fmt, ...)  LOGPOINT_FUNCTION_C(LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, keys, kLogPointLabelNone, fmt, ## __VA_ARGS__)
#else
#define lpwarning(keys, fmt, ...)   LOGPOINT_EMPTY
#define lpcwarning(keys, fmt, ...)  LOGPOINT_EMPTY
#endif
      

#if LOGPOINT_ENABLE_TRACE
#define LPTRACE                     LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatNone)

#define lptrace(keys)               _lpSoftLogMessage("", 0, "TRACE", keys, self, _cmd, "")
#define lpctrace(keys)              _lpSoftLogMessage("", 0, "TRACE", keys, NULL, NULL, "")
#else
#define LPTRACE                     LOGPOINT_EMPTY
#define lptrace(keys)				LOGPOINT_EMPTY
#define lpctrace(keys)				LOGPOINT_EMPTY
#endif

#warning c version missing
#define lpdebugOneLessThan1 lpdebug0
#define lpdebugOneLessThan2 lpdebug1
#define lpdebugOneLessThan3 lpdebug2
#define lpdebugOneLessThan4 lpdebug3
#define lpdebugOneLessThan5 lpdebug4
#define lpdebugOneLessThan6 lpdebug5



#if LOGPOINT_ENABLE_DEBUG

#define lpdebug(keys, fmt, ...)     LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, keys, NULL, fmt, ## __VA_ARGS__)
#define lpcdebug(keys, fmt, ...)     LOGPOINT_FUNCTION_C(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, keys, NULL, fmt, ## __VA_ARGS__)

#define lpsingle(keys, label, fmt, value)  LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, keys, label " =", fmt, value)
#define lpcsingle(keys, label, fmt, value)  LOGPOINT_FUNCTION_C(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, keys, label " =", fmt, value)

#define lpInt(keys, value)          lpsingle(keys, #value, "%d", (int) value)
#define lpcInt(keys, value)         lpcsingle(keys, #value, "%d", (int) value)

#define lpDouble(keys, value)       _lpSoftLogMessage(#value, LOGPOINT_OBJC, "DEBUG", keys, self, _cmd, "%s = %f", #value, value)
#define lpcDouble(keys, value)       _lpSoftLogMessage(#value, LOGPOINT_C, "DEBUG", keys, NULL, NULL, "%s = %f", #value, value)

#define lpshow(value)               _lpSoftLogMessage(#value, LOGPOINT_OBJC, "DEBUG", #value, self, _cmd, "%@", value)
#define lpcshow(value)               _lpSoftLogMessage(#value, LOGPOINT_C, "DEBUG", #value, NULL, NULL, "%@", value)

#ifdef __OBJC__

#warning c versions missing

#define lpdebug0()					                LOGPOINT_METHOD_OBJC(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatNone)
#define lpdebug1(v1)					LOGPOINT_METHOD_OBJC_AUTO_VALUE1(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, kLogPointLabelNone, #v1, (v1))
#define lpdebug2(v1, v2)				LOGPOINT_METHOD_OBJC_AUTO_VALUE2(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, kLogPointLabelNone, #v1, (v1), #v2, (v2))
#define lpdebug3(v1, v2, v3)			LOGPOINT_METHOD_OBJC_AUTO_VALUE3(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, kLogPointLabelNone, #v1, (v1), #v2, (v2), #v3, (v3))
#define lpdebug4(v1, v2, v3, v4)		LOGPOINT_METHOD_OBJC_AUTO_VALUE4(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, kLogPointLabelNone, #v1, (v1), #v2, (v2), #v3, (v3), #v4, (v4))
#define lpdebug5(v1, v2, v3, v4, v5)	LOGPOINT_METHOD_OBJC_AUTO_VALUE5(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, kLogPointLabelNone, #v1, (v1), #v2, (v2), #v3, (v3), #v4, (v4), #v5, (v5))

#define lpdebugn(...) ER_VARARGS_TO_ONELESSTHAN(lpdebug, ## __VA_ARGS__)
#define lpcdebugn(...) ER_VARARGS_TO_ONELESSTHAN(lpcdebug, ## __VA_ARGS__)

#define lpdebug_expr(value)  LOGPOINT_METHOD_OBJC_AUTO_EXPR( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, kLogPointLabelNone, #value, (value))
#define lpcdebug_expr(value)  LOGPOINT_FUNCTION_C_AUTO_EXPR( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, kLogPointLabelNone, #value, (value))

#define lpdebug_return(value) return LOGPOINT_METHOD_OBJC_AUTO_EXPR( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, "return", #value, (value))
#define lpcdebug_return(value) return LOGPOINT_FUNCTION_C_AUTO_EXPR( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, "return", #value, (value))

#else

/* no non-objC AUTO support right now - there is some stuff in experimental for plain c but it is gruesome */

#endif

#else
/* !LOGPOINT_ENABLE_DEBUG */

#define lpdebug(keys, ...)          LOGPOINT_EMPTY
#define lpcdebug(keys, ...)         LOGPOINT_EMPTY

#define lpInt(keys, ...)            LOGPOINT_EMPTY
#define lpcInt(keys, ...)           LOGPOINT_EMPTY

#define lpDouble(keys, ...)         LOGPOINT_EMPTY
#define lpcDouble(keys, ...)        LOGPOINT_EMPTY

#define lpshow(v)		    LOGPOINT_EMPTY
#define lpcshow(v)		    LOGPOINT_EMPTY

#ifdef __OBJC__

#define lpdebug0()					    LOGPOINT_EMPTY
#define lpdebug1(v1)					LOGPOINT_EMPTY
#define lpdebug2(v1, v2)				LOGPOINT_EMPTY
#define lpdebug3(v1, v2, v3)			LOGPOINT_EMPTY
#define lpdebug4(v1, v2, v3, v4)		LOGPOINT_EMPTY
#define lpdebug5(v1, v2, v3, v4, v5)	LOGPOINT_EMPTY

#define lpdebugn(...)			LOGPOINT_EMPTY
#define lpcdebugn(...)			LOGPOINT_EMPTY

#define lpdebug_expr(expr)		(expr)
#define lpcdebug_expr(expr)		(expr)

#define lpdebug_return(expr)		return (expr)
#define lpcdebug_return(expr)		return (expr)
#endif
/* __OBJC__ */

#endif
/* LOGPOINT_ENABLE_DEBUG */


#if LOGPOINT_ENABLE_NOTES
#define lpFIXME(fmt, ...)           lpHardLogMessage(LOGPOINT_OBJC, "FIXME", NULL, self, _cmd, fmt, ## __VA_ARGS__)
#define lpcFIXME(fmt, ...)           lpHardLogMessage(LOGPOINT_C, "FIXME", NULL, NULL, NULL, fmt, ## __VA_ARGS__)
#define lpTODO(fmt, ...)            lpHardLogMessage(LOGPOINT_OBJC, "TODO", NULL, self, _cmd, fmt, ## __VA_ARGS__)
#define lpcTODO(fmt, ...)            lpHardLogMessage(LOGPOINT_C, "TODO", NULL, NULL, NULL, fmt, ## __VA_ARGS__)
#else
#define lpFIXME(fmt, ...)           LOGPOINT_EMPTY
#define lpcFIXME(fmt, ...)          LOGPOINT_EMPTY
#define lpTODO(fmt, ...)            LOGPOINT_EMPTY
#define lpcTODO(fmt, ...)           LOGPOINT_EMPTY
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


#define LPABSTRACT                  lpassert(NULL, @"needs implementation in subclass")


#endif
/* __LOGPOINTS_DEFAULT_H__ */

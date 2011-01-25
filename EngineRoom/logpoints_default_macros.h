
/*
 * logpoints_default_macros.h - generated code - do not edit
 */

#ifndef __LOGPOINTS_DEFAULT_MACROS_H__
#define __LOGPOINTS_DEFAULT_MACROS_H__ 1

#include "logpoints_base_macros.h"

#if LOGPOINT_ENABLE_SWITCH

#define lpcswitchf(fmt, ...)              lplog_c_printf_v1(LOGPOINT_FLAGS_SWITCH, kLogPointKindSwitch, kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpkcswitchf(keys, fmt, ...)       lplog_c_printf_v1(LOGPOINT_FLAGS_SWITCH, kLogPointKindSwitch, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpswitchf(fmt, ...)               lplog_objc_printf_v1(LOGPOINT_FLAGS_SWITCH, kLogPointKindSwitch, kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpkswitchf(keys, fmt, ...)        lplog_objc_printf_v1(LOGPOINT_FLAGS_SWITCH, kLogPointKindSwitch, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#if __OBJC__

#define lpcswitch(...)                    lplog_c_auto_multiple_v1(LOGPOINT_FLAGS_SWITCH, kLogPointKindSwitch, kLogPointKeysNone, kLogPointLabelNone, ## __VA_ARGS__ )

#define lpkcswitch(keys, ...)             lplog_c_auto_multiple_v1(LOGPOINT_FLAGS_SWITCH, kLogPointKindSwitch, (keys), kLogPointLabelNone, ## __VA_ARGS__ )

#define lpswitch(...)                     lplog_objc_auto_multiple_v1(LOGPOINT_FLAGS_SWITCH, kLogPointKindSwitch, kLogPointKeysNone, kLogPointLabelNone, ## __VA_ARGS__ )

#define lpkswitch(keys, ...)              lplog_objc_auto_multiple_v1(LOGPOINT_FLAGS_SWITCH, kLogPointKindSwitch, (keys), kLogPointLabelNone, ## __VA_ARGS__ )

#endif
/* __OBJC__ */

#else
/* ! LOGPOINT_ENABLE_SWITCH */

#define lpcswitchf(fmt, ...)              LOGPOINT_ZERO
#define lpkcswitchf(keys, fmt, ...)       LOGPOINT_ZERO
#define lpswitchf(fmt, ...)               LOGPOINT_ZERO
#define lpkswitchf(keys, fmt, ...)        LOGPOINT_ZERO

#if __OBJC__

#define lpcswitch(...)                    LOGPOINT_ZERO
#define lpkcswitch(keys, ...)             LOGPOINT_ZERO
#define lpswitch(...)                     LOGPOINT_ZERO
#define lpkswitch(keys, ...)              LOGPOINT_ZERO

#endif
/* __OBJC__ */

#endif
/* LOGPOINT_ENABLE_SWITCH */

#if LOGPOINT_ENABLE_ASSERT

#define lpcassertf(cond, fmt, ...)        ({ LOGPOINT *__lpRet = NULL; if( ! (cond) ) { __lpRet = lplog_c_printf_v1(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, kLogPointKeysNone, #cond ":", kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__); if( __lpRet ) { if( LOGPOINT_IS_ASSERT( *__lpRet ) ) { NSLog(@"ASSERTION - HARD - FIXME" ); abort(); } else { NSLog(@"ASSERTION - SOFT - FIXME"); } } } __lpRet; })

#define lpkcassertf(keys, cond, fmt, ...) ({ LOGPOINT *__lpRet = NULL; if( ! (cond) ) { __lpRet = lplog_c_printf_v1(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, (keys), #cond ":", kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__); if( __lpRet ) { if( LOGPOINT_IS_ASSERT( *__lpRet ) ) { NSLog(@"ASSERTION - HARD - FIXME" ); abort(); } else { NSLog(@"ASSERTION - SOFT - FIXME"); } } } __lpRet; })

#define lpassertf(cond, fmt, ...)         ({ LOGPOINT *__lpRet = NULL; if( ! (cond) ) { __lpRet = lplog_objc_printf_v1(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, kLogPointKeysNone, #cond ":", kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__); if( __lpRet ) { if( LOGPOINT_IS_ASSERT( *__lpRet ) ) { NSLog(@"ASSERTION - HARD - FIXME" ); abort(); } else { NSLog(@"ASSERTION - SOFT - FIXME"); } } } __lpRet; })

#define lpkassertf(keys, cond, fmt, ...)  ({ LOGPOINT *__lpRet = NULL; if( ! (cond) ) { __lpRet = lplog_objc_printf_v1(LOGPOINT_FLAGS_ASSERT, kLogPointKindAssert, (keys), #cond ":", kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__); if( __lpRet ) { if( LOGPOINT_IS_ASSERT( *__lpRet ) ) { NSLog(@"ASSERTION - HARD - FIXME" ); abort(); } else { NSLog(@"ASSERTION - SOFT - FIXME"); } } } __lpRet; })

#else
/* ! LOGPOINT_ENABLE_ASSERT */

#define lpcassertf(cond, fmt, ...)        LOGPOINT_ZERO
#define lpkcassertf(keys, cond, fmt, ...) LOGPOINT_ZERO
#define lpassertf(cond, fmt, ...)         LOGPOINT_ZERO
#define lpkassertf(keys, cond, fmt, ...)  LOGPOINT_ZERO

#endif
/* LOGPOINT_ENABLE_ASSERT */

#if LOGPOINT_ENABLE_TRACE

#define lpctracef(fmt, ...)               lplog_c_printf_v1(LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpkctracef(keys, fmt, ...)        lplog_c_printf_v1(LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lptracef(fmt, ...)                lplog_objc_printf_v1(LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpktracef(keys, fmt, ...)         lplog_objc_printf_v1(LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#if __OBJC__

#define lpctrace_expr(value)              lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, kLogPointKeysNone, #value, (value) )

#define return_lpctrace(value)            return lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, kLogPointKeysNone, "return", (value) )

#define lpkctrace_expr(keys, value)       lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, (keys), #value, (value) )

#define return_lpkctrace(keys, value)     return lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, (keys), "return", (value) )

#define lptrace_expr(value)               lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, kLogPointKeysNone, #value, (value) )

#define return_lptrace(value)             return lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, kLogPointKeysNone, "return", (value) )

#define lpktrace_expr(keys, value)        lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, (keys), #value, (value) )

#define return_lpktrace(keys, value)      return lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, (keys), "return", (value) )

#define lpctrace(...)                     lplog_c_auto_multiple_v1(LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, kLogPointKeysNone, kLogPointLabelNone, ## __VA_ARGS__ )

#define lpkctrace(keys, ...)              lplog_c_auto_multiple_v1(LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, (keys), kLogPointLabelNone, ## __VA_ARGS__ )

#define lptrace(...)                      lplog_objc_auto_multiple_v1(LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, kLogPointKeysNone, kLogPointLabelNone, ## __VA_ARGS__ )

#define lpktrace(keys, ...)               lplog_objc_auto_multiple_v1(LOGPOINT_FLAGS_TRACE, kLogPointKindTrace, (keys), kLogPointLabelNone, ## __VA_ARGS__ )

#endif
/* __OBJC__ */

#else
/* ! LOGPOINT_ENABLE_TRACE */

#define lpctracef(fmt, ...)               LOGPOINT_ZERO
#define lpkctracef(keys, fmt, ...)        LOGPOINT_ZERO
#define lptracef(fmt, ...)                LOGPOINT_ZERO
#define lpktracef(keys, fmt, ...)         LOGPOINT_ZERO

#if __OBJC__

#define lpctrace_expr(value)              (value)
#define return_lpctrace(value)            return (value)
#define lpkctrace_expr(keys, value)       (value)
#define return_lpkctrace(keys, value)     return (value)
#define lptrace_expr(value)               (value)
#define return_lptrace(value)             return (value)
#define lpktrace_expr(keys, value)        (value)
#define return_lpktrace(keys, value)      return (value)
#define lpctrace(...)                     LOGPOINT_ZERO
#define lpkctrace(keys, ...)              LOGPOINT_ZERO
#define lptrace(...)                      LOGPOINT_ZERO
#define lpktrace(keys, ...)               LOGPOINT_ZERO

#endif
/* __OBJC__ */

#endif
/* LOGPOINT_ENABLE_TRACE */

#if LOGPOINT_ENABLE_DEBUG

#define lpcdebugf(fmt, ...)               lplog_c_printf_v1(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpkcdebugf(keys, fmt, ...)        lplog_c_printf_v1(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpdebugf(fmt, ...)                lplog_objc_printf_v1(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpkdebugf(keys, fmt, ...)         lplog_objc_printf_v1(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#if __OBJC__

#define lpcdebug_expr(value)              lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, #value, (value) )

#define return_lpcdebug(value)            return lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, "return", (value) )

#define lpkcdebug_expr(keys, value)       lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, (keys), #value, (value) )

#define return_lpkcdebug(keys, value)     return lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, (keys), "return", (value) )

#define lpdebug_expr(value)               lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, #value, (value) )

#define return_lpdebug(value)             return lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, "return", (value) )

#define lpkdebug_expr(keys, value)        lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, (keys), #value, (value) )

#define return_lpkdebug(keys, value)      return lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, (keys), "return", (value) )

#define lpcdebug(...)                     lplog_c_auto_multiple_v1(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, kLogPointLabelNone, ## __VA_ARGS__ )

#define lpkcdebug(keys, ...)              lplog_c_auto_multiple_v1(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, (keys), kLogPointLabelNone, ## __VA_ARGS__ )

#define lpdebug(...)                      lplog_objc_auto_multiple_v1(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, kLogPointKeysNone, kLogPointLabelNone, ## __VA_ARGS__ )

#define lpkdebug(keys, ...)               lplog_objc_auto_multiple_v1(LOGPOINT_FLAGS_DEBUG, kLogPointKindDebug, (keys), kLogPointLabelNone, ## __VA_ARGS__ )

#endif
/* __OBJC__ */

#else
/* ! LOGPOINT_ENABLE_DEBUG */

#define lpcdebugf(fmt, ...)               LOGPOINT_ZERO
#define lpkcdebugf(keys, fmt, ...)        LOGPOINT_ZERO
#define lpdebugf(fmt, ...)                LOGPOINT_ZERO
#define lpkdebugf(keys, fmt, ...)         LOGPOINT_ZERO

#if __OBJC__

#define lpcdebug_expr(value)              (value)
#define return_lpcdebug(value)            return (value)
#define lpkcdebug_expr(keys, value)       (value)
#define return_lpkcdebug(keys, value)     return (value)
#define lpdebug_expr(value)               (value)
#define return_lpdebug(value)             return (value)
#define lpkdebug_expr(keys, value)        (value)
#define return_lpkdebug(keys, value)      return (value)
#define lpcdebug(...)                     LOGPOINT_ZERO
#define lpkcdebug(keys, ...)              LOGPOINT_ZERO
#define lpdebug(...)                      LOGPOINT_ZERO
#define lpkdebug(keys, ...)               LOGPOINT_ZERO

#endif
/* __OBJC__ */

#endif
/* LOGPOINT_ENABLE_DEBUG */

#if LOGPOINT_ENABLE_INFO

#define lpcinfof(fmt, ...)                lplog_c_printf_v1(LOGPOINT_FLAGS_INFO, kLogPointKindInfo, kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpkcinfof(keys, fmt, ...)         lplog_c_printf_v1(LOGPOINT_FLAGS_INFO, kLogPointKindInfo, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpinfof(fmt, ...)                 lplog_objc_printf_v1(LOGPOINT_FLAGS_INFO, kLogPointKindInfo, kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpkinfof(keys, fmt, ...)          lplog_objc_printf_v1(LOGPOINT_FLAGS_INFO, kLogPointKindInfo, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#if __OBJC__

#define lpcinfo_expr(value)               lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_INFO, kLogPointKindInfo, kLogPointKeysNone, #value, (value) )

#define return_lpcinfo(value)             return lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_INFO, kLogPointKindInfo, kLogPointKeysNone, "return", (value) )

#define lpkcinfo_expr(keys, value)        lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_INFO, kLogPointKindInfo, (keys), #value, (value) )

#define return_lpkcinfo(keys, value)      return lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_INFO, kLogPointKindInfo, (keys), "return", (value) )

#define lpinfo_expr(value)                lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_INFO, kLogPointKindInfo, kLogPointKeysNone, #value, (value) )

#define return_lpinfo(value)              return lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_INFO, kLogPointKindInfo, kLogPointKeysNone, "return", (value) )

#define lpkinfo_expr(keys, value)         lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_INFO, kLogPointKindInfo, (keys), #value, (value) )

#define return_lpkinfo(keys, value)       return lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_INFO, kLogPointKindInfo, (keys), "return", (value) )

#define lpcinfo(...)                      lplog_c_auto_multiple_v1(LOGPOINT_FLAGS_INFO, kLogPointKindInfo, kLogPointKeysNone, kLogPointLabelNone, ## __VA_ARGS__ )

#define lpkcinfo(keys, ...)               lplog_c_auto_multiple_v1(LOGPOINT_FLAGS_INFO, kLogPointKindInfo, (keys), kLogPointLabelNone, ## __VA_ARGS__ )

#define lpinfo(...)                       lplog_objc_auto_multiple_v1(LOGPOINT_FLAGS_INFO, kLogPointKindInfo, kLogPointKeysNone, kLogPointLabelNone, ## __VA_ARGS__ )

#define lpkinfo(keys, ...)                lplog_objc_auto_multiple_v1(LOGPOINT_FLAGS_INFO, kLogPointKindInfo, (keys), kLogPointLabelNone, ## __VA_ARGS__ )

#endif
/* __OBJC__ */

#else
/* ! LOGPOINT_ENABLE_INFO */

#define lpcinfof(fmt, ...)                LOGPOINT_ZERO
#define lpkcinfof(keys, fmt, ...)         LOGPOINT_ZERO
#define lpinfof(fmt, ...)                 LOGPOINT_ZERO
#define lpkinfof(keys, fmt, ...)          LOGPOINT_ZERO

#if __OBJC__

#define lpcinfo_expr(value)               (value)
#define return_lpcinfo(value)             return (value)
#define lpkcinfo_expr(keys, value)        (value)
#define return_lpkcinfo(keys, value)      return (value)
#define lpinfo_expr(value)                (value)
#define return_lpinfo(value)              return (value)
#define lpkinfo_expr(keys, value)         (value)
#define return_lpkinfo(keys, value)       return (value)
#define lpcinfo(...)                      LOGPOINT_ZERO
#define lpkcinfo(keys, ...)               LOGPOINT_ZERO
#define lpinfo(...)                       LOGPOINT_ZERO
#define lpkinfo(keys, ...)                LOGPOINT_ZERO

#endif
/* __OBJC__ */

#endif
/* LOGPOINT_ENABLE_INFO */

#if LOGPOINT_ENABLE_NOTICE

#define lpcnoticef(fmt, ...)              lplog_c_printf_v1(LOGPOINT_FLAGS_NOTICE, kLogPointKindNotice, kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpkcnoticef(keys, fmt, ...)       lplog_c_printf_v1(LOGPOINT_FLAGS_NOTICE, kLogPointKindNotice, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpnoticef(fmt, ...)               lplog_objc_printf_v1(LOGPOINT_FLAGS_NOTICE, kLogPointKindNotice, kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpknoticef(keys, fmt, ...)        lplog_objc_printf_v1(LOGPOINT_FLAGS_NOTICE, kLogPointKindNotice, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#if __OBJC__

#define lpcnotice_expr(value)             lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_NOTICE, kLogPointKindNotice, kLogPointKeysNone, #value, (value) )

#define return_lpcnotice(value)           return lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_NOTICE, kLogPointKindNotice, kLogPointKeysNone, "return", (value) )

#define lpkcnotice_expr(keys, value)      lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_NOTICE, kLogPointKindNotice, (keys), #value, (value) )

#define return_lpkcnotice(keys, value)    return lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_NOTICE, kLogPointKindNotice, (keys), "return", (value) )

#define lpnotice_expr(value)              lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_NOTICE, kLogPointKindNotice, kLogPointKeysNone, #value, (value) )

#define return_lpnotice(value)            return lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_NOTICE, kLogPointKindNotice, kLogPointKeysNone, "return", (value) )

#define lpknotice_expr(keys, value)       lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_NOTICE, kLogPointKindNotice, (keys), #value, (value) )

#define return_lpknotice(keys, value)     return lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_NOTICE, kLogPointKindNotice, (keys), "return", (value) )

#define lpcnotice(...)                    lplog_c_auto_multiple_v1(LOGPOINT_FLAGS_NOTICE, kLogPointKindNotice, kLogPointKeysNone, kLogPointLabelNone, ## __VA_ARGS__ )

#define lpkcnotice(keys, ...)             lplog_c_auto_multiple_v1(LOGPOINT_FLAGS_NOTICE, kLogPointKindNotice, (keys), kLogPointLabelNone, ## __VA_ARGS__ )

#define lpnotice(...)                     lplog_objc_auto_multiple_v1(LOGPOINT_FLAGS_NOTICE, kLogPointKindNotice, kLogPointKeysNone, kLogPointLabelNone, ## __VA_ARGS__ )

#define lpknotice(keys, ...)              lplog_objc_auto_multiple_v1(LOGPOINT_FLAGS_NOTICE, kLogPointKindNotice, (keys), kLogPointLabelNone, ## __VA_ARGS__ )

#endif
/* __OBJC__ */

#else
/* ! LOGPOINT_ENABLE_NOTICE */

#define lpcnoticef(fmt, ...)              LOGPOINT_ZERO
#define lpkcnoticef(keys, fmt, ...)       LOGPOINT_ZERO
#define lpnoticef(fmt, ...)               LOGPOINT_ZERO
#define lpknoticef(keys, fmt, ...)        LOGPOINT_ZERO

#if __OBJC__

#define lpcnotice_expr(value)             (value)
#define return_lpcnotice(value)           return (value)
#define lpkcnotice_expr(keys, value)      (value)
#define return_lpkcnotice(keys, value)    return (value)
#define lpnotice_expr(value)              (value)
#define return_lpnotice(value)            return (value)
#define lpknotice_expr(keys, value)       (value)
#define return_lpknotice(keys, value)     return (value)
#define lpcnotice(...)                    LOGPOINT_ZERO
#define lpkcnotice(keys, ...)             LOGPOINT_ZERO
#define lpnotice(...)                     LOGPOINT_ZERO
#define lpknotice(keys, ...)              LOGPOINT_ZERO

#endif
/* __OBJC__ */

#endif
/* LOGPOINT_ENABLE_NOTICE */

#if LOGPOINT_ENABLE_WARNING

#define lpcwarningf(fmt, ...)             lplog_c_printf_v1(LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpkcwarningf(keys, fmt, ...)      lplog_c_printf_v1(LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpwarningf(fmt, ...)              lplog_objc_printf_v1(LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpkwarningf(keys, fmt, ...)       lplog_objc_printf_v1(LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#if __OBJC__

#define lpcwarning_expr(value)            lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, kLogPointKeysNone, #value, (value) )

#define return_lpcwarning(value)          return lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, kLogPointKeysNone, "return", (value) )

#define lpkcwarning_expr(keys, value)     lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, (keys), #value, (value) )

#define return_lpkcwarning(keys, value)   return lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, (keys), "return", (value) )

#define lpwarning_expr(value)             lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, kLogPointKeysNone, #value, (value) )

#define return_lpwarning(value)           return lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, kLogPointKeysNone, "return", (value) )

#define lpkwarning_expr(keys, value)      lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, (keys), #value, (value) )

#define return_lpkwarning(keys, value)    return lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, (keys), "return", (value) )

#define lpcwarning(...)                   lplog_c_auto_multiple_v1(LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, kLogPointKeysNone, kLogPointLabelNone, ## __VA_ARGS__ )

#define lpkcwarning(keys, ...)            lplog_c_auto_multiple_v1(LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, (keys), kLogPointLabelNone, ## __VA_ARGS__ )

#define lpwarning(...)                    lplog_objc_auto_multiple_v1(LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, kLogPointKeysNone, kLogPointLabelNone, ## __VA_ARGS__ )

#define lpkwarning(keys, ...)             lplog_objc_auto_multiple_v1(LOGPOINT_FLAGS_WARNING, kLogPointKindWarning, (keys), kLogPointLabelNone, ## __VA_ARGS__ )

#endif
/* __OBJC__ */

#else
/* ! LOGPOINT_ENABLE_WARNING */

#define lpcwarningf(fmt, ...)             LOGPOINT_ZERO
#define lpkcwarningf(keys, fmt, ...)      LOGPOINT_ZERO
#define lpwarningf(fmt, ...)              LOGPOINT_ZERO
#define lpkwarningf(keys, fmt, ...)       LOGPOINT_ZERO

#if __OBJC__

#define lpcwarning_expr(value)            (value)
#define return_lpcwarning(value)          return (value)
#define lpkcwarning_expr(keys, value)     (value)
#define return_lpkcwarning(keys, value)   return (value)
#define lpwarning_expr(value)             (value)
#define return_lpwarning(value)           return (value)
#define lpkwarning_expr(keys, value)      (value)
#define return_lpkwarning(keys, value)    return (value)
#define lpcwarning(...)                   LOGPOINT_ZERO
#define lpkcwarning(keys, ...)            LOGPOINT_ZERO
#define lpwarning(...)                    LOGPOINT_ZERO
#define lpkwarning(keys, ...)             LOGPOINT_ZERO

#endif
/* __OBJC__ */

#endif
/* LOGPOINT_ENABLE_WARNING */

#if LOGPOINT_ENABLE_ERROR

#define lpcerrorf(fmt, ...)               lplog_c_printf_v1(LOGPOINT_FLAGS_ERROR, kLogPointKindError, kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpkcerrorf(keys, fmt, ...)        lplog_c_printf_v1(LOGPOINT_FLAGS_ERROR, kLogPointKindError, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lperrorf(fmt, ...)                lplog_objc_printf_v1(LOGPOINT_FLAGS_ERROR, kLogPointKindError, kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#define lpkerrorf(keys, fmt, ...)         lplog_objc_printf_v1(LOGPOINT_FLAGS_ERROR, kLogPointKindError, (keys), kLogPointLabelNone, kLogPointFormatInfoNone, (fmt), ## __VA_ARGS__)

#if __OBJC__

#define lpcerror_expr(value)              lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_ERROR, kLogPointKindError, kLogPointKeysNone, #value, (value) )

#define return_lpcerror(value)            return lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_ERROR, kLogPointKindError, kLogPointKeysNone, "return", (value) )

#define lpkcerror_expr(keys, value)       lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_ERROR, kLogPointKindError, (keys), #value, (value) )

#define return_lpkcerror(keys, value)     return lplog_c_auto_rvalue_v1( LOGPOINT_FLAGS_ERROR, kLogPointKindError, (keys), "return", (value) )

#define lperror_expr(value)               lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_ERROR, kLogPointKindError, kLogPointKeysNone, #value, (value) )

#define return_lperror(value)             return lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_ERROR, kLogPointKindError, kLogPointKeysNone, "return", (value) )

#define lpkerror_expr(keys, value)        lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_ERROR, kLogPointKindError, (keys), #value, (value) )

#define return_lpkerror(keys, value)      return lplog_objc_auto_rvalue_v1( LOGPOINT_FLAGS_ERROR, kLogPointKindError, (keys), "return", (value) )

#define lpcerror(...)                     lplog_c_auto_multiple_v1(LOGPOINT_FLAGS_ERROR, kLogPointKindError, kLogPointKeysNone, kLogPointLabelNone, ## __VA_ARGS__ )

#define lpkcerror(keys, ...)              lplog_c_auto_multiple_v1(LOGPOINT_FLAGS_ERROR, kLogPointKindError, (keys), kLogPointLabelNone, ## __VA_ARGS__ )

#define lperror(...)                      lplog_objc_auto_multiple_v1(LOGPOINT_FLAGS_ERROR, kLogPointKindError, kLogPointKeysNone, kLogPointLabelNone, ## __VA_ARGS__ )

#define lpkerror(keys, ...)               lplog_objc_auto_multiple_v1(LOGPOINT_FLAGS_ERROR, kLogPointKindError, (keys), kLogPointLabelNone, ## __VA_ARGS__ )

#endif
/* __OBJC__ */

#else
/* ! LOGPOINT_ENABLE_ERROR */

#define lpcerrorf(fmt, ...)               LOGPOINT_ZERO
#define lpkcerrorf(keys, fmt, ...)        LOGPOINT_ZERO
#define lperrorf(fmt, ...)                LOGPOINT_ZERO
#define lpkerrorf(keys, fmt, ...)         LOGPOINT_ZERO

#if __OBJC__

#define lpcerror_expr(value)              (value)
#define return_lpcerror(value)            return (value)
#define lpkcerror_expr(keys, value)       (value)
#define return_lpkcerror(keys, value)     return (value)
#define lperror_expr(value)               (value)
#define return_lperror(value)             return (value)
#define lpkerror_expr(keys, value)        (value)
#define return_lpkerror(keys, value)      return (value)
#define lpcerror(...)                     LOGPOINT_ZERO
#define lpkcerror(keys, ...)              LOGPOINT_ZERO
#define lperror(...)                      LOGPOINT_ZERO
#define lpkerror(keys, ...)               LOGPOINT_ZERO

#endif
/* __OBJC__ */

#endif
/* LOGPOINT_ENABLE_ERROR */

#endif
/* __LOGPOINTS_DEFAULT_MACROS_H__ */


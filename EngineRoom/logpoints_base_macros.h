
/*
 * logpoints_base_macros.h - generated code - do not edit
 */

#ifndef __LOGPOINTS_BASE_MACROS_H__
#define __LOGPOINTS_BASE_MACROS_H__ 1

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#import <objc/runtime.h>
#endif

#include "logpoints_api.h"

#if LOGPOINT_ENABLE_LPLOG

#define lplog_c_printf_v1(flags, kind, keys, label, fmtInfo, fmt, ...)                LOGPOINT_CREATE((flags) | LOGPOINT_C, (kind), (keys), (label), NULL, NULL, (fmtInfo), (fmt), ## __VA_ARGS__)

#define lplog_objc_printf_v1(flags, kind, keys, label, fmtInfo, fmt, ...)             LOGPOINT_CREATE((flags) | LOGPOINT_OBJC, (kind), (keys), (label), self, _cmd, (fmtInfo), (fmt), ## __VA_ARGS__)

#if __OBJC__
/* currently no auto support for C or CXX - see experimental */

#define lplog_c_auto_rvalue_v1(flags, kind, keys, label, value)                       ({ \
        __typeof__(value) __lpValueTmp = (value); \
        id __lpMsg = LOGPOINT_FORMAT_VALUE(__lpValueTmp, kLogPointLabelNone); \
        (void) LOGPOINT_CREATE( (flags) | LOGPOINT_C, (kind), (keys), (label), NULL, NULL, #value, "%@", __lpMsg ); \
        __lpValueTmp; })

#define lplog_c_auto_multiple_v1(flags, kind, keys, label, ...)                       ER_VARARGS_TO_NONZERO_ARGS(_lplog_c_auto_v1_4lessThan_, (flags) | LOGPOINT_C, (kind), (keys), (label), ## __VA_ARGS__)

#define lplog_objc_auto_rvalue_v1(flags, kind, keys, label, value)                    ({ \
        __typeof__(value) __lpValueTmp = (value); \
        id __lpMsg = LOGPOINT_FORMAT_VALUE(__lpValueTmp, kLogPointLabelNone); \
        (void) LOGPOINT_CREATE( (flags) | LOGPOINT_OBJC, (kind), (keys), (label), self, _cmd, #value, "%@", __lpMsg ); \
        __lpValueTmp; })

#define lplog_objc_auto_multiple_v1(flags, kind, keys, label, ...)                    ER_VARARGS_TO_NONZERO_ARGS(_lplog_objc_auto_v1_4lessThan_, (flags) | LOGPOINT_OBJC, (kind), (keys), (label), ## __VA_ARGS__)

#endif
/* __OBJC__ */

#else
/* ! LOGPOINT_ENABLE_LPLOG */

#define lplog_c_printf_v1(flags, kind, keys, label, fmtInfo, fmt, ...)                LOGPOINT_ZERO

#define lplog_objc_printf_v1(flags, kind, keys, label, fmtInfo, fmt, ...)             LOGPOINT_ZERO

#if __OBJC__
/* currently no auto support for C or CXX - see experimental */

#define lplog_c_auto_rvalue_v1(flags, kind, keys, label, value)                       (value)

#define lplog_c_auto_multiple_v1(flags, kind, keys, label, ...)                       LOGPOINT_ZERO

#define lplog_objc_auto_rvalue_v1(flags, kind, keys, label, value)                    (value)

#define lplog_objc_auto_multiple_v1(flags, kind, keys, label, ...)                    LOGPOINT_ZERO

#endif
/* __OBJC__ */

#endif
/* LOGPOINT_ENABLE_LPLOG */

/* ==================================================== */
/* ==== PRIVATE PARTS - will change without notice ==== */
/* ==================================================== */

/* used by auto-varargs macro ER_VARARGS_TO_NONZERO_ARGS */

#define _lplog_c_auto_v1_4lessThan_4(flags, kind, keys, label)                        LOGPOINT_CREATE((flags) | LOGPOINT_C, (kind), (keys), (label), NULL, NULL, kLogPointFormatInfoNone, kLogPointFormatNone)
#define _lplog_c_auto_v1_4lessThan_5(flags, kind, keys, label, v1)                    LOGPOINT_CREATE((flags) | LOGPOINT_C, (kind), (keys), (label), NULL, NULL, #v1, "%@",  \
			LOGPOINT_FORMAT_VALUE( (v1), #v1 ))
#define _lplog_c_auto_v1_4lessThan_6(flags, kind, keys, label, v1, v2)                LOGPOINT_CREATE((flags) | LOGPOINT_C, (kind), (keys), (label), NULL, NULL, #v1 ", " #v2, "%@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), #v1 ),  \
			LOGPOINT_FORMAT_VALUE( (v2), #v2 ))
#define _lplog_c_auto_v1_4lessThan_7(flags, kind, keys, label, v1, v2, v3)            LOGPOINT_CREATE((flags) | LOGPOINT_C, (kind), (keys), (label), NULL, NULL, #v1 ", " #v2 ", " #v3, "%@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), #v1 ),  \
			LOGPOINT_FORMAT_VALUE( (v2), #v2 ),  \
			LOGPOINT_FORMAT_VALUE( (v3), #v3 ))
#define _lplog_c_auto_v1_4lessThan_8(flags, kind, keys, label, v1, v2, v3, v4)        LOGPOINT_CREATE((flags) | LOGPOINT_C, (kind), (keys), (label), NULL, NULL, #v1 ", " #v2 ", " #v3 ", " #v4, "%@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), #v1 ),  \
			LOGPOINT_FORMAT_VALUE( (v2), #v2 ),  \
			LOGPOINT_FORMAT_VALUE( (v3), #v3 ),  \
			LOGPOINT_FORMAT_VALUE( (v4), #v4 ))
#define _lplog_c_auto_v1_4lessThan_9(flags, kind, keys, label, v1, v2, v3, v4, v5)    LOGPOINT_CREATE((flags) | LOGPOINT_C, (kind), (keys), (label), NULL, NULL, #v1 ", " #v2 ", " #v3 ", " #v4 ", " #v5, "%@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), #v1 ),  \
			LOGPOINT_FORMAT_VALUE( (v2), #v2 ),  \
			LOGPOINT_FORMAT_VALUE( (v3), #v3 ),  \
			LOGPOINT_FORMAT_VALUE( (v4), #v4 ),  \
			LOGPOINT_FORMAT_VALUE( (v5), #v5 ))
#define _lplog_objc_auto_v1_4lessThan_4(flags, kind, keys, label)                     LOGPOINT_CREATE((flags) | LOGPOINT_OBJC, (kind), (keys), (label), self, _cmd, kLogPointFormatInfoNone, kLogPointFormatNone)
#define _lplog_objc_auto_v1_4lessThan_5(flags, kind, keys, label, v1)                 LOGPOINT_CREATE((flags) | LOGPOINT_OBJC, (kind), (keys), (label), self, _cmd, #v1, "%@",  \
			LOGPOINT_FORMAT_VALUE( (v1), #v1 ))
#define _lplog_objc_auto_v1_4lessThan_6(flags, kind, keys, label, v1, v2)             LOGPOINT_CREATE((flags) | LOGPOINT_OBJC, (kind), (keys), (label), self, _cmd, #v1 ", " #v2, "%@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), #v1 ),  \
			LOGPOINT_FORMAT_VALUE( (v2), #v2 ))
#define _lplog_objc_auto_v1_4lessThan_7(flags, kind, keys, label, v1, v2, v3)         LOGPOINT_CREATE((flags) | LOGPOINT_OBJC, (kind), (keys), (label), self, _cmd, #v1 ", " #v2 ", " #v3, "%@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), #v1 ),  \
			LOGPOINT_FORMAT_VALUE( (v2), #v2 ),  \
			LOGPOINT_FORMAT_VALUE( (v3), #v3 ))
#define _lplog_objc_auto_v1_4lessThan_8(flags, kind, keys, label, v1, v2, v3, v4)     LOGPOINT_CREATE((flags) | LOGPOINT_OBJC, (kind), (keys), (label), self, _cmd, #v1 ", " #v2 ", " #v3 ", " #v4, "%@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), #v1 ),  \
			LOGPOINT_FORMAT_VALUE( (v2), #v2 ),  \
			LOGPOINT_FORMAT_VALUE( (v3), #v3 ),  \
			LOGPOINT_FORMAT_VALUE( (v4), #v4 ))
#define _lplog_objc_auto_v1_4lessThan_9(flags, kind, keys, label, v1, v2, v3, v4, v5) LOGPOINT_CREATE((flags) | LOGPOINT_OBJC, (kind), (keys), (label), self, _cmd, #v1 ", " #v2 ", " #v3 ", " #v4 ", " #v5, "%@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), #v1 ),  \
			LOGPOINT_FORMAT_VALUE( (v2), #v2 ),  \
			LOGPOINT_FORMAT_VALUE( (v3), #v3 ),  \
			LOGPOINT_FORMAT_VALUE( (v4), #v4 ),  \
			LOGPOINT_FORMAT_VALUE( (v5), #v5 ))

#endif
/* __LOGPOINTS_BASE_MACROS_H__ */


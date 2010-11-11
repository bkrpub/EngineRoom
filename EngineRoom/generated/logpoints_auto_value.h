/*
 * logpoints_auto_value.h - generated code
 */

#ifndef __LOGPOINTS_AUTO_VALUE_H__
#define __LOGPOINTS_AUTO_VALUE_H__ 1

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE0(flags, kind, keys, label) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), kLogPointFormatInfoNone, kLogPointFormatNone )

#define LOGPOINT_FUNCTION_C_AUTO_VALUE0(flags, kind, keys, label) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), kLogPointFormatInfoNone, kLogPointFormatNone )

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE1(flags, kind, keys, label, l1, v1) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1,  "%@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ) )

#define LOGPOINT_FUNCTION_C_AUTO_VALUE1(flags, kind, keys, label, l1, v1) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1,  "%@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ) )

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE2(flags, kind, keys, label, l1, v1, l2, v2) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2,  "%@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ) )

#define LOGPOINT_FUNCTION_C_AUTO_VALUE2(flags, kind, keys, label, l1, v1, l2, v2) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2,  "%@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ) )

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE3(flags, kind, keys, label, l1, v1, l2, v2, l3, v3) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3,  "%@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ) )

#define LOGPOINT_FUNCTION_C_AUTO_VALUE3(flags, kind, keys, label, l1, v1, l2, v2, l3, v3) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3,  "%@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ) )

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE4(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4,  "%@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ) )

#define LOGPOINT_FUNCTION_C_AUTO_VALUE4(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4,  "%@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ) )

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE5(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5,  "%@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ) )

#define LOGPOINT_FUNCTION_C_AUTO_VALUE5(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5,  "%@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ) )

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE6(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6,  "%@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ) )

#define LOGPOINT_FUNCTION_C_AUTO_VALUE6(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6,  "%@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ) )

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE7(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7,  "%@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ) )

#define LOGPOINT_FUNCTION_C_AUTO_VALUE7(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7,  "%@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ) )

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE8(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ) )

#define LOGPOINT_FUNCTION_C_AUTO_VALUE8(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ) )

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE9(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ) )

#define LOGPOINT_FUNCTION_C_AUTO_VALUE9(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ) )

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE10(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ) )

#define LOGPOINT_FUNCTION_C_AUTO_VALUE10(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ) )


#endif
 /* __LOGPOINTS_AUTO_VALUE_H__ */

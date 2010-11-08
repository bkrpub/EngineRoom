/*
 * logpoints_auto_value.h - generated code
 */

#ifndef __LOGPOINTS_AUTO_VALUE_H__
#define __LOGPOINTS_AUTO_VALUE_H__ 1

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE1(flags, kind, keys, label, l1, v1) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1,  "%@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE1(flags, kind, keys, label, l1, v1) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1,  "%@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE2(flags, kind, keys, label, l1, v1, l2, v2) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2,  "%@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE2(flags, kind, keys, label, l1, v1, l2, v2) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2,  "%@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE3(flags, kind, keys, label, l1, v1, l2, v2, l3, v3) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3,  "%@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE3(flags, kind, keys, label, l1, v1, l2, v2, l3, v3) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3,  "%@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE4(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4,  "%@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE4(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4,  "%@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE5(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5,  "%@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE5(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5,  "%@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE6(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6,  "%@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE6(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6,  "%@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE7(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7,  "%@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE7(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7,  "%@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE8(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE8(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ) \
		)

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
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ) \
		)

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
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ) \
		)

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
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ) \
		)

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
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE11(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE11(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE12(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE12(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE13(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12, l13, v13) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12 ", " l13,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ),  \
			LOGPOINT_FORMAT_VALUE( (v13), (l13) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE13(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12, l13, v13) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12 ", " l13,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ),  \
			LOGPOINT_FORMAT_VALUE( (v13), (l13) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE14(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12, l13, v13, l14, v14) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12 ", " l13 ", " l14,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ),  \
			LOGPOINT_FORMAT_VALUE( (v13), (l13) ),  \
			LOGPOINT_FORMAT_VALUE( (v14), (l14) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE14(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12, l13, v13, l14, v14) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12 ", " l13 ", " l14,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ),  \
			LOGPOINT_FORMAT_VALUE( (v13), (l13) ),  \
			LOGPOINT_FORMAT_VALUE( (v14), (l14) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE15(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12, l13, v13, l14, v14, l15, v15) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12 ", " l13 ", " l14 ", " l15,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ),  \
			LOGPOINT_FORMAT_VALUE( (v13), (l13) ),  \
			LOGPOINT_FORMAT_VALUE( (v14), (l14) ),  \
			LOGPOINT_FORMAT_VALUE( (v15), (l15) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE15(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12, l13, v13, l14, v14, l15, v15) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12 ", " l13 ", " l14 ", " l15,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ),  \
			LOGPOINT_FORMAT_VALUE( (v13), (l13) ),  \
			LOGPOINT_FORMAT_VALUE( (v14), (l14) ),  \
			LOGPOINT_FORMAT_VALUE( (v15), (l15) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE16(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12, l13, v13, l14, v14, l15, v15, l16, v16) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12 ", " l13 ", " l14 ", " l15 ", " l16,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ),  \
			LOGPOINT_FORMAT_VALUE( (v13), (l13) ),  \
			LOGPOINT_FORMAT_VALUE( (v14), (l14) ),  \
			LOGPOINT_FORMAT_VALUE( (v15), (l15) ),  \
			LOGPOINT_FORMAT_VALUE( (v16), (l16) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE16(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12, l13, v13, l14, v14, l15, v15, l16, v16) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12 ", " l13 ", " l14 ", " l15 ", " l16,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ),  \
			LOGPOINT_FORMAT_VALUE( (v13), (l13) ),  \
			LOGPOINT_FORMAT_VALUE( (v14), (l14) ),  \
			LOGPOINT_FORMAT_VALUE( (v15), (l15) ),  \
			LOGPOINT_FORMAT_VALUE( (v16), (l16) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE17(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12, l13, v13, l14, v14, l15, v15, l16, v16, l17, v17) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12 ", " l13 ", " l14 ", " l15 ", " l16 ", " l17,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ),  \
			LOGPOINT_FORMAT_VALUE( (v13), (l13) ),  \
			LOGPOINT_FORMAT_VALUE( (v14), (l14) ),  \
			LOGPOINT_FORMAT_VALUE( (v15), (l15) ),  \
			LOGPOINT_FORMAT_VALUE( (v16), (l16) ),  \
			LOGPOINT_FORMAT_VALUE( (v17), (l17) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE17(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12, l13, v13, l14, v14, l15, v15, l16, v16, l17, v17) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12 ", " l13 ", " l14 ", " l15 ", " l16 ", " l17,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ),  \
			LOGPOINT_FORMAT_VALUE( (v13), (l13) ),  \
			LOGPOINT_FORMAT_VALUE( (v14), (l14) ),  \
			LOGPOINT_FORMAT_VALUE( (v15), (l15) ),  \
			LOGPOINT_FORMAT_VALUE( (v16), (l16) ),  \
			LOGPOINT_FORMAT_VALUE( (v17), (l17) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE18(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12, l13, v13, l14, v14, l15, v15, l16, v16, l17, v17, l18, v18) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12 ", " l13 ", " l14 ", " l15 ", " l16 ", " l17 ", " l18,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ),  \
			LOGPOINT_FORMAT_VALUE( (v13), (l13) ),  \
			LOGPOINT_FORMAT_VALUE( (v14), (l14) ),  \
			LOGPOINT_FORMAT_VALUE( (v15), (l15) ),  \
			LOGPOINT_FORMAT_VALUE( (v16), (l16) ),  \
			LOGPOINT_FORMAT_VALUE( (v17), (l17) ),  \
			LOGPOINT_FORMAT_VALUE( (v18), (l18) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE18(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12, l13, v13, l14, v14, l15, v15, l16, v16, l17, v17, l18, v18) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12 ", " l13 ", " l14 ", " l15 ", " l16 ", " l17 ", " l18,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ),  \
			LOGPOINT_FORMAT_VALUE( (v13), (l13) ),  \
			LOGPOINT_FORMAT_VALUE( (v14), (l14) ),  \
			LOGPOINT_FORMAT_VALUE( (v15), (l15) ),  \
			LOGPOINT_FORMAT_VALUE( (v16), (l16) ),  \
			LOGPOINT_FORMAT_VALUE( (v17), (l17) ),  \
			LOGPOINT_FORMAT_VALUE( (v18), (l18) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE19(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12, l13, v13, l14, v14, l15, v15, l16, v16, l17, v17, l18, v18, l19, v19) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12 ", " l13 ", " l14 ", " l15 ", " l16 ", " l17 ", " l18 ", " l19,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ),  \
			LOGPOINT_FORMAT_VALUE( (v13), (l13) ),  \
			LOGPOINT_FORMAT_VALUE( (v14), (l14) ),  \
			LOGPOINT_FORMAT_VALUE( (v15), (l15) ),  \
			LOGPOINT_FORMAT_VALUE( (v16), (l16) ),  \
			LOGPOINT_FORMAT_VALUE( (v17), (l17) ),  \
			LOGPOINT_FORMAT_VALUE( (v18), (l18) ),  \
			LOGPOINT_FORMAT_VALUE( (v19), (l19) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE19(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12, l13, v13, l14, v14, l15, v15, l16, v16, l17, v17, l18, v18, l19, v19) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12 ", " l13 ", " l14 ", " l15 ", " l16 ", " l17 ", " l18 ", " l19,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ),  \
			LOGPOINT_FORMAT_VALUE( (v13), (l13) ),  \
			LOGPOINT_FORMAT_VALUE( (v14), (l14) ),  \
			LOGPOINT_FORMAT_VALUE( (v15), (l15) ),  \
			LOGPOINT_FORMAT_VALUE( (v16), (l16) ),  \
			LOGPOINT_FORMAT_VALUE( (v17), (l17) ),  \
			LOGPOINT_FORMAT_VALUE( (v18), (l18) ),  \
			LOGPOINT_FORMAT_VALUE( (v19), (l19) ) \
		)

#define LOGPOINT_METHOD_OBJC_AUTO_VALUE20(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12, l13, v13, l14, v14, l15, v15, l16, v16, l17, v17, l18, v18, l19, v19, l20, v20) \
		LOGPOINT_METHOD_OBJC2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12 ", " l13 ", " l14 ", " l15 ", " l16 ", " l17 ", " l18 ", " l19 ", " l20,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ),  \
			LOGPOINT_FORMAT_VALUE( (v13), (l13) ),  \
			LOGPOINT_FORMAT_VALUE( (v14), (l14) ),  \
			LOGPOINT_FORMAT_VALUE( (v15), (l15) ),  \
			LOGPOINT_FORMAT_VALUE( (v16), (l16) ),  \
			LOGPOINT_FORMAT_VALUE( (v17), (l17) ),  \
			LOGPOINT_FORMAT_VALUE( (v18), (l18) ),  \
			LOGPOINT_FORMAT_VALUE( (v19), (l19) ),  \
			LOGPOINT_FORMAT_VALUE( (v20), (l20) ) \
		)

#define LOGPOINT_FUNCTION_C_AUTO_VALUE20(flags, kind, keys, label, l1, v1, l2, v2, l3, v3, l4, v4, l5, v5, l6, v6, l7, v7, l8, v8, l9, v9, l10, v10, l11, v11, l12, v12, l13, v13, l14, v14, l15, v15, l16, v16, l17, v17, l18, v18, l19, v19, l20, v20) \
		LOGPOINT_FUNCTION_C2( (flags), (kind), (keys), (label), l1 ", " l2 ", " l3 ", " l4 ", " l5 ", " l6 ", " l7 ", " l8 ", " l9 ", " l10 ", " l11 ", " l12 ", " l13 ", " l14 ", " l15 ", " l16 ", " l17 ", " l18 ", " l19 ", " l20,  "%@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@ | %@",  \
			LOGPOINT_FORMAT_VALUE( (v1), (l1) ),  \
			LOGPOINT_FORMAT_VALUE( (v2), (l2) ),  \
			LOGPOINT_FORMAT_VALUE( (v3), (l3) ),  \
			LOGPOINT_FORMAT_VALUE( (v4), (l4) ),  \
			LOGPOINT_FORMAT_VALUE( (v5), (l5) ),  \
			LOGPOINT_FORMAT_VALUE( (v6), (l6) ),  \
			LOGPOINT_FORMAT_VALUE( (v7), (l7) ),  \
			LOGPOINT_FORMAT_VALUE( (v8), (l8) ),  \
			LOGPOINT_FORMAT_VALUE( (v9), (l9) ),  \
			LOGPOINT_FORMAT_VALUE( (v10), (l10) ),  \
			LOGPOINT_FORMAT_VALUE( (v11), (l11) ),  \
			LOGPOINT_FORMAT_VALUE( (v12), (l12) ),  \
			LOGPOINT_FORMAT_VALUE( (v13), (l13) ),  \
			LOGPOINT_FORMAT_VALUE( (v14), (l14) ),  \
			LOGPOINT_FORMAT_VALUE( (v15), (l15) ),  \
			LOGPOINT_FORMAT_VALUE( (v16), (l16) ),  \
			LOGPOINT_FORMAT_VALUE( (v17), (l17) ),  \
			LOGPOINT_FORMAT_VALUE( (v18), (l18) ),  \
			LOGPOINT_FORMAT_VALUE( (v19), (l19) ),  \
			LOGPOINT_FORMAT_VALUE( (v20), (l20) ) \
		)


#endif
 /* __LOGPOINTS_AUTO_VALUE_H__ */

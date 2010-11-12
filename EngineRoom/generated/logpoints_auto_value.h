
/*
 * logpoints_auto_value.h - generated code - do not edit
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



#endif
/* __LOGPOINTS_AUTO_VALUE_H__ */


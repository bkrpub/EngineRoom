#ifndef __LOGPOINTS_NSLOG_H__
#define __LOGPOINTS_NSLOG_H__ 1

#define lpNSLog(fmt, ...) lplog_c_printf_v1( LOGPOINT_FLAGS_DEBUG | LOGPOINT_NSSTRING, "NSLog", kLogPointKeysNone, kLogPointLabelNone, kLogPointFormatInfoNone, fmt, ## __VA_ARGS__ ) 
/* (?) lpNSLogv */

/* this is convenient but will prevent using the symbol NSLog as a function pointer */
#define NSLog lpNSLog

#endif
/* __LOGPOINTS_NSLOG_H__ */

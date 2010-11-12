#ifndef __LOGPOINTS_NSLOG_H__
#define __LOGPOINTS_NSLOG_H__ 1

#define lpNSLog(fmt, ...) LOGPOINT_FUNCTION_C_NS( LOGPOINT_NOFLAGS, "NSLog", kLogPointKeysNone, kLogPointLabelNone, fmt, ## __VA_ARGS__ ) 
/* (?) lpNSLogv */

/* this is convenient but will prevent using the symbol NSLog as a function pointer */
#define NSLog lpNSLog

#endif
/* __LOGPOINTS_NSLOG_H__ */

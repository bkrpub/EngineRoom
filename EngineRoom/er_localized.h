
#ifndef __ER_LOCALIZED_H__
#define __ER_LOCALIZED_H__ 1

/* extra nil is to avoid non-literal format without args warning */

#define ER_LOCALIZED_FORMAT(fmt, ...) [NSString stringWithFormat: NSLocalizedString((fmt), @""), ## __VA_ARGS__, nil] 

#endif
/* __ER_LOCALIZED_H__ */

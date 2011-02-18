
#ifndef __ER_CONVENIENCE_H__
#define __ER_CONVENIENCE_H__ 1

#import <EngineRoom/ERUtility.h>

#pragma mark -
#pragma mark Localization

/* extra nil is to avoid non-literal format without args warning */
#define ER_LOCALIZED_FORMAT(fmt, ...) [NSString stringWithFormat: NSLocalizedString((fmt), @""), ## __VA_ARGS__, nil] 



#pragma mark -
#pragma mark NSError Tools

#define ER_SET_NSERROR(errorPtr, theDomain, theCode, userInfoObjectsAndKeys, ...) \
do { if( nil != errorPtr ) \
*(errorPtr) = [NSError errorWithDomain: (theDomain) code: (theCode) userInfo: (userInfoObjectsAndKeys) ? [NSDictionary dictionaryWithObjectsAndKeys: (userInfoObjectsAndKeys), ## __VA_ARGS__, nil] : nil]; \
} while(0)

#define ER_PRESENT_NSERROR_REASON(presenter, theDomain, theCode, reasonFormat, ...) \
({ NSError *__presentError = nil; \
ER_SET_NSERROR((&__presentError), (theDomain), (theCode), ER_LOCALIZED_FORMAT(reasonFormat, ## __VA_ARGS__), NSLocalizedFailureReasonErrorKey); \
if( nil != __presentError ) { [((presenter) ? (NSResponder *)(presenter) : NSApp) presentError: __presentError]; } })

#define ER_SET_NSERROR_REASON(errorPtr, theDomain, theCode, reasonFormat, ...) \
ER_SET_NSERROR((errorPtr), (theDomain), (theCode), ER_LOCALIZED_FORMAT(reasonFormat, ## __VA_ARGS__), NSLocalizedFailureReasonErrorKey)

#define ER_CHECK_NSERROR_REASON(assertion, errorPtr, theDomain, theCode, reasonFormat, ...) \
({ BOOL __check = YES; if( ! (assertion) ) { ER_SET_NSERROR_REASON((errorPtr), (theDomain), (theCode), (reasonFormat), ## __VA_ARGS__); __check = NO; } __check; })			

#define ER_CHECK_NSERROR_REASON_RETURN_NIL(assertion, errorPtr, theDomain, theCode, reasonFormat, ...) \
do{ if( NO == ER_CHECK_NSERROR_REASON((assertion), (errorPtr), (theDomain), (theCode), (reasonFormat), ## __VA_ARGS__) ) { return nil; } } while(0)

#define ER_CHECK_NSERROR_REASON_RETURN_NO(assertion, errorPtr, theDomain, theCode, reasonFormat, ...) \
do{ if( NO == ER_CHECK_NSERROR_REASON((assertion), (errorPtr), (theDomain), (theCode), (reasonFormat), ## __VA_ARGS__) ) { return NO; } } while(0)


#define ER_PRECONDITION_NSERROR_RETURN_NO(cond, errorPtr) \
ER_CHECK_NSERROR_REASON_RETURN_NO((cond), (errorPtr), NSPOSIXErrorDomain, EINVAL, @"errorPreconditionNotSatisfied: %s", #cond)

#define ER_PRECONDITION_NSERROR_RETURN_NIL(cond, errorPtr) \
ER_CHECK_NSERROR_REASON_RETURN_NIL((cond), (errorPtr), NSPOSIXErrorDomain, EINVAL, @"errorPreconditionNotSatisfied: %s", #cond)


#pragma mark -
#pragma mark Good stuff from Mike Ash (posted on his blog, renamed for EngineRoom)

#define ER_IDARRAY(...) (id []){ __VA_ARGS__ }
#define ER_IDCOUNT(...) (sizeof(ER_IDARRAY(__VA_ARGS__)) / sizeof(id))

#define ER_ARRAY(...) [NSArray arrayWithObjects: ER_IDARRAY(__VA_ARGS__) count: ER_IDCOUNT(__VA_ARGS__)]

// function is in ERUtility.m
#define ER_DICT(...) ERDictionaryWithKeysAndObjects(ER_IDARRAY(__VA_ARGS__), ER_IDCOUNT(__VA_ARGS__) / 2)

#define ER_NUMBER_YES [NSNumber numberWithBool: YES]
#define ER_NUMBER_NO  [NSNumber numberWithBool: NO]

#define ER_NUMBER_0   [NSNumber numberWithInteger: 0]

#endif
/* __ER_CONVENIENCE_H__ */


#import "NSPropertyListSerialization_ERBackPortExtensions.h"

#import <AvailabilityMacros.h>

@implementation NSPropertyListSerialization ( ERBackPortExtensions )

+ (id) er_propertyListWithData: (NSData *) data options: (NSUInteger) options error: (NSError **) outError
{
	id plist;

#if ( TARGET_OS_OSX && MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_6 ) || \
	( TARGET_OS_IPHONE && __IPHONE_OS_VERSION_MIN_REQUIRED < __IPHONE_4_0 )
	plist = [self propertyListWithData: data options: NSPropertyListMutableContainers format: NULL error: outError];
#else
	NSString *errorString = nil;
	plist = [self propertyListFromData: data mutabilityOption: NSPropertyListMutableContainers format: NULL errorDescription: &errorString];
	
	if( nil == plist && nil != outError ) {
		*outError = [NSError errorWithDomain: NSPOSIXErrorDomain code: EINVAL userInfo: 
					 [NSDictionary dictionaryWithObjectsAndKeys:
					  errorString, NSLocalizedFailureReasonErrorKey,
					  errorString, NSLocalizedString(@"CANT_PARSE_PLIST", @"can not parse property list data"),
					  nil]];
	}	
#endif
	
	return plist;
}

@end

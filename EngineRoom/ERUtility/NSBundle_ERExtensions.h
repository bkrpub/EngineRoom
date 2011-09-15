
#import <Foundation/Foundation.h>

extern NSString *kERBundleBuildConfiguration;

@interface NSBundle (ResourceExtensions)

- (NSData *) er_dataResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) dataOptions error: (NSError **) outError;

- (id) er_propertyListResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) plistOptions error: (NSError **) outError;

@end

@interface NSBundle (ERInfoDictionaryExtensions)

- (NSString *) er_machineReadableVersionString;

- (NSString *) er_humanReadableVersionString;

@end
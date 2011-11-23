
#import <Foundation/Foundation.h>

extern NSString *kERBundleBuildConfiguration;

@interface NSBundle (ResourceExtensions)

- (NSURL *) er_URLForResource: (NSString *) name withExtension: (NSString *) extension error: (NSError **) outError;

- (NSData *) er_dataResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) dataOptions error: (NSError **) outError;

- (NSString *) er_stringResource: (NSString *) name ofType: (NSString *) type encoding: (NSStringEncoding) encoding error: (NSError **) outError;

- (NSString *) er_stringResource: (NSString *) name ofType: (NSString *) type error: (NSError **) outError;

- (id) er_propertyListResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) plistOptions error: (NSError **) outError;

@end

@interface NSBundle (ERInfoDictionaryExtensions)

- (NSString *) er_machineReadableVersionString;

- (NSString *) er_humanReadableVersionString;

@end
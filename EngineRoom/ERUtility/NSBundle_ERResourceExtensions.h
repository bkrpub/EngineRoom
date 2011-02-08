
#import <Foundation/Foundation.h>

@interface NSBundle (ResourceExtensions)

- (NSData *) er_dataResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) dataOptions error: (NSError **) outError;

- (id) er_propertyListResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) plistOptions error: (NSError **) outError;

@end

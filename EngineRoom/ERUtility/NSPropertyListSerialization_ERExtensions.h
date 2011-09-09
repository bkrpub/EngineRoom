#import <Foundation/Foundation.h>

@interface NSPropertyListSerialization ( ERBackPortExtensions )

// compiled to the same as without er_ prefix for OSX >= 10.6 and IOS >= 4.0, an approximation for older systems
+ (id) er_propertyListWithData: (NSData *) data options: (NSUInteger) options error: (NSError **) outError;

@end

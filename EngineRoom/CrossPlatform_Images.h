
#import <EngineRoom/CrossPlatform_Images.h>

@interface CrossPlatform (Images)

+ (id) platformSpecificBitmapImageNamed: (NSString *) name;
+ (id) platformSpecificBitmapImageWithContentsOfURL: (NSURL *) URL error: (NSError **) error;

+ (CGImageRef) CGImageNamed: (NSString *) name;
+ (CGImageRef) cachedCGImageNamed: (NSString *) name;

+ (CGImageRef) CGImageWithContentsOfURL: (NSURL *) URL error: (NSError **) error;

@end


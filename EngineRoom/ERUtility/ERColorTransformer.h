#import <EngineRoom/ERValueTransformer.h>

#if TARGET_OS_OSX
@interface ERColorNSColorTransformer : ERValueTransformer
@end
#endif

@interface ERColorCGColorTransformer : ERValueTransformer
@end

@interface ERColorGenericRGBAStringTransformer : ERValueTransformer
@end

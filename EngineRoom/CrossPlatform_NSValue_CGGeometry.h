
#import <EngineRoom/CrossPlatform_Target.h>

@interface NSValue ( CrossPlatform_CGGeometry ) 

#if TARGET_OS_OSX

+ (NSValue *) valueWithCGPoint: (CGPoint) point;
+ (NSValue *) valueWithCGSize: (CGSize) size;
+ (NSValue *) valueWithCGRect: (CGRect) rect;

- (CGPoint) CGPointValue;
- (CGSize) CGSizeValue;
- (CGRect) CGRectValue;

#endif

@end



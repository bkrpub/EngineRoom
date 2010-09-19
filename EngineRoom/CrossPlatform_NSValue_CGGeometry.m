
#import "CrossPlatform_NSValue_CGGeometry.h"

@implementation NSValue ( CrossPlatform_CGGeometry ) 

#if TARGET_OS_OSX

+ (NSValue *) valueWithCGPoint: (CGPoint) point { return [NSValue valueWithPoint: NSPointFromCGPoint(point)]; }
+ (NSValue *) valueWithCGSize:  (CGSize)  size  { return [NSValue valueWithSize: NSSizeFromCGSize(size)]; }
+ (NSValue *) valueWithCGRect:  (CGRect)  rect  { return [NSValue valueWithRect: NSRectFromCGRect(rect)]; }

- (CGPoint) CGPointValue { return NSPointToCGPoint([self pointValue]); }
- (CGSize) CGSizeValue   { return NSSizeToCGSize([self sizeValue]); }
- (CGRect) CGRectValue   { return NSRectToCGRect([self rectValue]); }

#endif

@end


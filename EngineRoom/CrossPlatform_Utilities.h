#ifndef __CROSS_PLATFORM_UTILITIES_H__
#define __CROSS_PLATFORM_UTILITIES_H__ 1

#import <EngineRoom/CrossPlatform_Target.h>

#import <EngineRoom/CrossPlatform_NSValue_CGGeometry.h>
#import <EngineRoom/CrossPlatform_NSString_CGGeometry.h>


#if TARGET_OS_IPHONE

typedef CGRect  CPRect;
typedef CGPoint CPPoint;
typedef CGSize  CPSize;

#define CPView				UIView
#define CPViewController	UIViewController
#define CPApplication		UIApplication
#define CPColor				UIColor
#define CPRectFill(r)		UIRectFill(r)

#define CPWidth(r)	CGRectGetWidth(r)
#define CPHeight(r) CGRectGetHeight(r)
#define CPMinX(r)	CGRectGetMinY(r)
#define CPMaxX(r)   CGRectGetMaxX(r)
#define CPMinY(r)	CGRectGetMinY(r)
#define CPMaxY(r)   CGRectGetMaxY(r)
#define CPMidX(r)	CGRectGetMidX(r)
#define CPMidY(r)   CGRectGetMidY(r)

#define CPPointFromNSValue(v) [(v) CGPointValue]
#define CPSizeFromNSValue(v) [(v) CGSizeValue]
#define CPRectFromNSValue(v) [(v) CGRectValue]

#define CGPointFromNSValue(v) CPPointFromNSValue(v)
#define CGSizeFromNSValue(v) CPRectFromNSValue(v)
#define CGRectFromNSValue(v) CPRectFromNSValue(v)

#define NSPointFromCGPoint(x) (x)
#define NSSizeFromCGSize(x)   (x)
#define NSRectFromCGRect(x)   (x)

#define NSPointToCGPoint(x) (x)
#define NSSizeToCGSize(x)   (x)
#define NSRectToCGRect(x)   (x)

#endif

#if TARGET_OS_OSX

#define CPView				NSView
#define CPViewController	NSViewController
#define CPApplication		NSApplication
#define CPColor				NSColor
#define CPRectFill(r)		NSRectFill(r)

typedef NSRect  CPRect;
typedef NSPoint CPPoint;
typedef NSSize  CPSize;

#define CPWidth(r)	NSWidth(r)
#define CPHeight(r) NSHeight(r)
#define CPMinX(r)	NSMinX(r)
#define CPMaxX(r)   NSMaxX(r)
#define CPMinY(r)	NSMinY(r)
#define CPMaxY(r)   NSMaxY(r)
#define CPMidX(r)	NSMidX(r)
#define CPMidY(r)   NSMidY(r)

#define CPPointFromNSValue(v) [(v) pointValue]
#define CPSizeFromNSValue(v) [(v) sizeValue]
#define CPRectFromNSValue(v) [(v) rectValue]

#define CGPointFromNSValue(v) NSPointToCGPoint( CPPointFromNSValue(v) )
#define CGSizeFromNSValue(v) NSSizeToCGSize( CPSizeFromNSValue(v) )
#define CGRectFromNSValue(v) NSRectToCGRect( CPRectFromNSValue(v) )

#define CGPointFromString(s) NSPointToCGPoint( NSPointFromString( s ) ) 
#define CGSizeFromString(s) NSSizeToCGSize( NSSizeFromString( s ) ) 
#define CGRectFromString(s) NSRectToCGRect( NSRectFromString( s ) ) 

#define NSStringFromCGPoint(p) NSStringFromPoint( NSPointFromCGPoint( p ) )
#define NSStringFromCGSize(s) NSStringFromSize( NSSizeFromCGSize( s ) )
#define NSStringFromCGRect(r) NSStringFromRect( NSRectFromCGRect( r ) )

#endif


#endif
// __CROSS_PLATFORM_UTILITIES_H__

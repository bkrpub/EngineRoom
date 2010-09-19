#ifndef __CROSS_PLATFORM_CGGEOMETRY_H__
#define __CROSS_PLATFORM_CGGEOMETRY_H__ 1

#import <EngineRoom/CrossPlatform_Target.h>

#if TARGET_OS_OSX

#define CGPointFromString(s) NSPointToCGPoint( NSPointFromString( s ) ) 
#define CGSizeFromString(s) NSSizeToCGSize( NSSizeFromString( s ) ) 
#define CGRectFromString(s) NSRectToCGRect( NSRectFromString( s ) ) 

#define NSStringFromCGPoint(p) NSStringFromPoint( NSPointFromCGPoint( p ) )
#define NSStringFromCGSize(s) NSStringFromSize( NSSizeFromCGSize( s ) )
#define NSStringFromCGRect(r) NSStringFromRect( NSRectFromCGRect( r ) )

#endif

#endif
// __CROSS_PLATFORM_CGGEOMETRY_H__

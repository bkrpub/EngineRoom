//
//  ERCGUtilities.h
//  EngineRoom-iOS
//
//  Created by Bjoern Kriews on 20.11.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef EngineRoom_iOS_ERCGUtilities_h
#define EngineRoom_iOS_ERCGUtilities_h

// these CGAffine Utilities were kindly put into the public domain by Jeff LaMarche
// I like to recommend his blog at http://iphonedevelopment.blogspot.com/

#import <CoreGraphics/CoreGraphics.h>

#ifdef __cplusplus
extern "C" {
#endif
    
#define ERDegreesToRadian(x) (M_PI * x / 180.0)
#define ERRadiansToDegrees(x) (180.0 * x / M_PI)
    
    static inline ERCGAffineTransform CGAffineTransformMakeShear(CGFloat shearX, CGFloat shearY)
    {
        return CGAffineTransformMake(1.f, shearY, shearX, 1.f, 0.f, 0.f);
    }
    static inline ERCGAffineTransform CGAffineTransformShear(CGAffineTransform transform, CGFloat shearX, CGFloat shearY)
    {
        CGAffineTransform sheared = ERCGAffineTransformMakeShear(shearX, shearY);
        return CGAffineTransformConcat(transform, sheared);
    }
    static inline CGFloat ERCGAffineTransformGetDeltaX(CGAffineTransform transform) {return transform.tx;};
    static inline CGFloat ERCGAffineTransformGetDeltaY(CGAffineTransform transform) {return transform.ty;};
    static inline CGFloat ERCGAffineTransformGetScaleX(CGAffineTransform transform) {return sqrtf( (transform.a * transform.a) + (transform.c * transform.c) );};
    static inline CGFloat ERCGAffineTransformGetScaleY(CGAffineTransform transform) {return sqrtf( (transform.b * transform.b) + (transform.d * transform.d) );};
    static inline CGFloat ERCGAffineTransformGetShearX(CGAffineTransform transform) {return transform.b;};
    static inline CGFloat ERCGAffineTransformGetShearY(CGAffineTransform transform) {return transform.c;};
    static inline CGFloat ERCGPointAngleBetweenPoints(CGPoint first, CGPoint second) 
    {
        CGFloat dy = second.y - first.y;
        CGFloat dx = second.x - first.x;
        return atan2f(dy, dx);
    }
    static inline CGFloat ERCGAffineTransformGetRotation(CGAffineTransform transform)
    {
        // No exact way to get rotation out without knowing order of all previous operations
        // So, we'll cheat. We'll apply the transformation to two points and then determine the
        // angle betwen those two points
        
        CGPoint testPoint1 = CGPointMake(-100.f, 0.f);
        CGPoint testPoint2 = CGPointMake(100.f, 0.f);
        CGPoint transformed1 = CGPointApplyAffineTransform(testPoint1, transform);
        CGPoint transformed2 = CGPointApplyAffineTransform(testPoint2, transform);
        return ERCGPointAngleBetweenPoints(transformed1, transformed2);
    }
    
#ifdef __cplusplus
}
#endif

#endif

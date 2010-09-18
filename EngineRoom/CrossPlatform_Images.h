//
//  CrossPlatform.h
//
//  Created by Bjoern Kriews on 08.10.08.
//  Copyright 2008 Bjoern Kriews. All rights reserved.
//

#ifndef __CROSS_PLATFORM_H__
#define __CROSS_PLATFORM_H__ 1

#import <TargetConditionals.h>

#if TARGET_OS_MAC && ! TARGET_OS_IPHONE
// since TARGET_OS_MAC is defined for IPHONE too
#define TARGET_OS_OSX 1
#endif


#if TARGET_OS_IPHONE

#import <UIKit/UIKit.h>

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
#define CGPointFromNSValue(v) CPPointFromNSValue(v)

#define NSPointFromCGPoint(x) (x)
#define NSSizeFromCGSize(x)   (x)
#define NSRectFromCGRect(x)   (x)

#define NSPointToCGPoint(x) (x)
#define NSSizeToCGSize(x)   (x)
#define NSRectToCGRect(x)   (x)

#endif

#if TARGET_OS_OSX

#import <Cocoa/Cocoa.h>

#define CPView				NSView
#define CPViewController	NSViewController
#define CPApplication		NSApplication
#define CPColor				NSColor
#define CPRectFill(r)		NSRectFill(NSRectFromCGRect(r))

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

#define CGPointFromString(s) NSPointToCGPoint( NSPointFromString( s ) ) 
#define CGSizeFromString(s) NSSizeToCGSize( NSSizeFromString( s ) ) 
#define CGRectFromString(s) NSRectToCGRect( NSRectFromString( s ) ) 

#define NSStringFromCGPoint(p) NSStringFromPoint( NSPointFromCGPoint( p ) )
#define NSStringFromCGSize(s) NSStringFromSize( NSSizeFromCGSize( s ) )
#define NSStringFromCGRect(r) NSStringFromRect( NSRectFromCGRect( r ) )

#endif

@interface CrossPlatform : NSObject {

}

+ (id) platformSpecificBitmapImageNamed: (NSString *) name;
+ (id) platformSpecificBitmapImageWithContentsOfURL: (NSURL *) URL error: (NSError **) error;

+ (CGImageRef) CGImageNamed: (NSString *) name;
+ (CGImageRef) cachedCGImageNamed: (NSString *) name;

+ (CGImageRef) CGImageWithContentsOfURL: (NSURL *) URL error: (NSError **) error;

@end

#if TARGET_OS_OSX

@interface NSValue ( CrossPlatformAdditions ) 
+ (NSValue *) valueWithCGPoint: (CGPoint) point;
+ (NSValue *) valueWithCGSize: (CGSize) size;
+ (NSValue *) valueWithCGRect: (CGRect) rect;

- (CGPoint) CGPointValue;
- (CGSize) CGSizeValue;
- (CGRect) CGRectValue;

@end

#endif

#endif
// __CROSS_PLATFORM_H__

/*
 This file is part of EngineRoom, Copyright (c) 2007-2010 Bjoern Kriews, Hamburg - All rights reserved.

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

 Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer
 in the documentation and/or other materials provided with the distribution.

 Neither the name of the author nor the names of its contributors may be used to endorse or promote products derived from this
 software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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

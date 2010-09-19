#ifndef __CROSS_PLATFORM_TARGET_H__
#define __CROSS_PLATFORM_TARGET_H__ 1

#import <TargetConditionals.h>

#if TARGET_OS_MAC && ! TARGET_OS_IPHONE
// since TARGET_OS_MAC is defined for IPHONE too
#define TARGET_OS_OSX 1
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif

#if TARGET_OS_OSX
#import <Cocoa/Cocoa.h>
#endif

#endif
// __CROSS_PLATFORM_TARGET_H__


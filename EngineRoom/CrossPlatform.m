//
//  CrossPlatform.m
//
//  Created by Bjoern Kriews on 08.10.08.
//  Copyright 2008 Bjoern Kriews. All rights reserved.
//

#import "CrossPlatform.h"

static NSMutableDictionary *CGImageCache = nil;
static id idNull = nil;

void __attribute__((constructor)) construct(void) 
{
#ifdef TARGET_OS_IPHONE
	NSLog(@"initializing CrossPlatform for iPhone OS");
#else
	NSLog(@"initializing CrossPlatform for Mac OS X");
#endif

	if( nil == CGImageCache ) {
		CGImageCache = [[NSMutableDictionary alloc] init];
	}

	if( nil == idNull ) {
		idNull = [[NSNull null] retain];
	}
}


@implementation CrossPlatform

+ (id) platformSpecificBitmapImageNamed: (NSString *) name
{
#if TARGET_OS_IPHONE
	return [UIImage imageNamed: name];
#else
	return [[[NSImage imageNamed: [name stringByDeletingPathExtension]] representations] objectAtIndex: 0];
#endif
}

+ (id) platformSpecificBitmapImageWithContentsOfURL: (NSURL *) URL error: (NSError **) error
{

	if( nil != error ) {
		*error = nil;
	}

	NSData *imageData = [NSData dataWithContentsOfURL: URL options: 0 error: error];

	id image = imageData ?
#if TARGET_OS_IPHONE
	[UIImage imageWithData: imageData] 
#else
	[NSBitmapImageRep imageRepWithData: imageData]
#endif
	: nil;

	// NSLog(@"image for %@: %@", URL, image);

	return image;
}

+ (CGImageRef) CGImageWithContentsOfURL: (NSURL *) URL error: (NSError **) error
{
	return [[self platformSpecificBitmapImageWithContentsOfURL: URL error: error] CGImage];
}

+ (CGImageRef) CGImageNamed: (NSString *) name
{
	return [[self platformSpecificBitmapImageNamed: name] CGImage];
}

+ (CGImageRef) cachedCGImageNamed: (NSString *) name
{
	id image = nil;

	@synchronized(CGImageCache) {
			image = [CGImageCache objectForKey: name];
	
			if( nil == image ) {
				image = (id) [[self platformSpecificBitmapImageNamed: name] CGImage];
				[CGImageCache setObject: image ? image : idNull forKey: name];
			}
	}

	return (CGImageRef) ( image == idNull ? NULL : image );
}

@end


@implementation NSValue ( CrossPlatformAdditions ) 

#if TARGET_OS_OSX
+ (NSValue *) valueWithCGPoint: (CGPoint) point { return [NSValue valueWithPoint: NSPointFromCGPoint(point)]; }
+ (NSValue *) valueWithCGSize:  (CGSize)  size  { return [NSValue valueWithSize: NSSizeFromCGSize(size)]; }
+ (NSValue *) valueWithCGRect:  (CGRect)  rect  { return [NSValue valueWithRect: NSRectFromCGRect(rect)]; }

- (CGPoint) CGPointValue { return NSPointToCGPoint([self pointValue]); }
- (CGSize) CGSizeValue   { return NSSizeToCGSize([self sizeValue]); }
- (CGRect) CGRectValue   { return NSRectToCGRect([self rectValue]); }
#endif

@end


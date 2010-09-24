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

#import "CrossPlatform_Images.h"

static NSMutableDictionary *CGImageCache = nil;
static id idNull = nil;

void __attribute__((constructor)) construct(void) 
{
#if TARGET_OS_IPHONE
#elif TARGET_OS_OSX
#else
#error Unknown TARGET_OS
#endif

	if( nil == CGImageCache ) {
		CGImageCache = [[NSMutableDictionary alloc] init];
	}

	if( nil == idNull ) {
		idNull = [[NSNull null] retain];
	}
}


@implementation CrossPlatform (Images)

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

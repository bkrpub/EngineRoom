
#import "CrossPlatform_Images.h"

static NSMutableDictionary *CGImageCache = nil;
static id idNull = nil;

void __attribute__((constructor)) construct(void) 
{
#if TARGET_OS_IPHONE
	NSLog(@"initializing CrossPlatform_Images for iPhone OS");
#elif TARGET_OS_OSX
	NSLog(@"initializing CrossPlatform_Images for Mac OS X");
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

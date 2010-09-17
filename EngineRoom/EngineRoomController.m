//
//  EngineRoomController.m
//  EngineRoom
//
//  Created by Bjoern Kriews on 25.02.09.
//  Copyright 2009 Bjoern Kriews. All rights reserved.
//

#import "EngineRoomController.h"

@implementation EngineRoomController

+ (EngineRoomController *) sharedEngineRoomController
{
	static EngineRoomController *sharedEngineRoomController = nil;
	
	if( nil == sharedEngineRoomController ) {
		sharedEngineRoomController = [[EngineRoomController alloc] init];
	}

	return sharedEngineRoomController;		
}

#if TARGET_OS_OSX
- (BOOL) loadNib
{
	BOOL success = NO;

	NSNib *nib = [[NSNib alloc] initWithNibNamed: @"EngineRoom" bundle: [NSBundle bundleForClass: [self class]]];
	
	if( nil != nib ) {
		
		if( NO == [nib instantiateNibWithOwner: self topLevelObjects: &engineRoomTopLevelObjects] ) {
			NSLog(@"failed to instantiate EngineRoom.nib");

			engineRoomTopLevelObjects = nil;
			
		} else {
			[engineRoomTopLevelObjects retain];
			success = YES;
		}
		
		[nib release];
	} else {
		NSLog(@"failed to load EngineRoom.nib");
	}

	return success;
}
#endif

- (void) install
{
#if TARGET_OS_OSX
	NSMenu *mainMenu = [NSApp mainMenu];

	NSMenuItem *subMenuItem = [[[NSMenuItem alloc] initWithTitle: @"" action: NULL keyEquivalent: @""] autorelease];
	[mainMenu addItem: subMenuItem];

	[mainMenu setSubmenu: engineRoomMenu forItem: subMenuItem];
#endif

#if TARGET_OS_IPHONE
	NSLog(@"%s: no iOS specific install routine yet", __PRETTY_FUNCTION__);
#endif
}

- (id) init
{
	if( ( self = [super init] ) ) {
#if TARGET_OS_OSX
		[self loadNib];
#endif
	}

	return self;
}

- (void) dealloc
{
	[engineRoomTopLevelObjects release];
	[super dealloc];
}

@end

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
- (void) traceResponderChain: (id) currentResponder position: (NSInteger *) position
{
	while( nil != currentResponder ) {

		NSLog(@"Responder %2ld: %@", (long)*position, currentResponder);
		++*position;
		
		if( NSApp == currentResponder || [currentResponder isKindOfClass: [NSWindow class]] ) {
			id delegate = (NSApp == currentResponder) ? (id)[(NSApplication *)currentResponder delegate] : (id)[(NSWindow *)currentResponder delegate];
			if( delegate ) {
				NSLog(@"Responder %2ld: %@ (delegate of %@)", (long)*position, delegate, currentResponder);
				++*position;
			}
		}

		currentResponder = [currentResponder respondsToSelector: @selector(nextResponder)] ? [currentResponder nextResponder] : nil;
	}
}

- (IBAction) logResponderChain: (id) sender
{
		NSInteger position = 1;
		NSWindow *theKeyWindow = [NSApp keyWindow];
		NSWindow *theMainWindow = [NSApp mainWindow];

		NSLog(@"--- Responder Chain ---");

		[self traceResponderChain: [theKeyWindow firstResponder] position: &position];
		if( theKeyWindow != theMainWindow ) {
			[self traceResponderChain: [theMainWindow firstResponder] position: &position];
		}

		[self traceResponderChain: NSApp position: &position];

		if( [[NSBundle mainBundle] objectForInfoDictionaryKey: @"CFBundleDocumentTypes"] ) {
			[self traceResponderChain: [NSDocumentController sharedDocumentController] position: &position];
		}

		NSLog(@"--- End Responder Chain ---");
} 
#endif


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

- (void) installInMenuItem: (NSMenuItem *) menuItem
{
#if TARGET_OS_OSX
	NSString *menuIconPath = [[NSBundle bundleForClass: [self class]] pathForImageResource: @"MenuIcon.png"];

	if( nil == menuItem ) {

		menuItem = [[[NSMenuItem alloc] initWithTitle: @"" action: NULL keyEquivalent: @""] autorelease];

		NSMenu *mainMenu = [NSApp mainMenu];

		[mainMenu addItem: menuItem];
		[mainMenu setSubmenu: engineRoomMenu forItem: menuItem];

	} else {
		NSMenuItem *firstEngineRoomMenuItem = [engineRoomMenu itemAtIndex: 0];
		[menuItem setTarget: [firstEngineRoomMenuItem target]];
		[menuItem setAction: [firstEngineRoomMenuItem action]];

		[menuItem setSubmenu: engineRoomMenu];
	}

	if( nil != menuIconPath ) {
		[menuItem setImage: [[[NSImage alloc] initWithContentsOfFile: menuIconPath] autorelease]];
	}

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

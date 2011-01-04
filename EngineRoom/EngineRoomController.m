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

#if TARGET_OS_OSX
- (void) installInMenuItem: (NSMenuItem *) menuItem
{

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
}
#endif



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

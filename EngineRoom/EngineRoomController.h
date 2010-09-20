//
//  EngineRoomController.h
//  EngineRoom
//
//  Created by Bjoern Kriews on 25.02.09.
//  Copyright 2009 Bjoern Kriews. All rights reserved.
//

#import <EngineRoom/CrossPlatform.h>

@interface EngineRoomController : NSObject {
#if TARGET_OS_OSX
	IBOutlet NSMenu *engineRoomMenu;
#endif
	NSArray *engineRoomTopLevelObjects;
}

+ (EngineRoomController *) sharedEngineRoomController;

#if TARGET_OS_OSX
- (void) traceResponderChain: (id) currentResponder position: (NSInteger *) position;
- (IBAction) logResponderChain: (id) sender;
#endif

- (void) installInMenuItem: (NSMenuItem *) menuItem;

@end

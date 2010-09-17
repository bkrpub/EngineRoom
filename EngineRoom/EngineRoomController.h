//
//  EngineRoomController.h
//  EngineRoom
//
//  Created by Bjoern Kriews on 25.02.09.
//  Copyright 2009 Bjoern Kriews. All rights reserved.
//

#import <TargetConditionals.h>

@interface EngineRoomController : NSObject {
#if ! TARGET_OS_IPHONE
	IBOutlet NSMenu *engineRoomMenu;
#endif
	NSArray *engineRoomTopLevelObjects;
}

+ (EngineRoomController *) sharedEngineRoomController;

- (void) install;

@end

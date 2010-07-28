//
//  EngineRoom.h
//  EngineRoom
//
//  Created by Bjoern Kriews on 25.02.09.
//  Copyright 2009 Bjoern Kriews. All rights reserved.
//

#import <EngineRoom/CrossPlatform.h>

#import <EngineRoom/EngineRoomController.h>

#if TARGET_OS_OSX
#import <EngineRoom/LogPointsWindowController.h>
#import <EngineRoom/ConsoleWindowController.h>
#endif

#import <EngineRoom/logpoints_api.h>
#import <EngineRoom/er_util.h>
#import <EngineRoom/tracer.h>

@interface EngineRoom : NSObject {
}

@end

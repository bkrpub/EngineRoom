//
//  EngineRoom.m
//  EngineRoom
//
//  Created by Bjoern Kriews on 25.02.09.
//  Copyright 2009 Bjoern Kriews. All rights reserved.
//

#import "EngineRoom.h"


@implementation EngineRoom

- (void) awakeFromNib
{
	EngineRoomController *controller = [EngineRoomController sharedEngineRoomController];
	[controller install];
}


@end

#import "EngineRoom.h"


@implementation EngineRoom

- (void) awakeFromNib
{
	EngineRoomController *controller = [EngineRoomController sharedEngineRoomController];
	[controller install];
}


@end

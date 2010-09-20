
// controls definition of globals, see EngineRoom.h
#define __ENGINE_ROOM_M__ 1

#import "EngineRoom.h"

@implementation EngineRoom

static EngineRoom *sharedEngineRoom = nil;

#pragma mark -
#pragma mark Initialization

void __attribute__ ((constructor)) engineRoomConstructor(void)
{
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	[EngineRoom sharedEngineRoom];
	[pool drain];
}

+ (id)sharedEngineRoom
{
	@synchronized(self) {
        if (sharedEngineRoom == nil) {
            [[[super alloc] init] release]; // assignment not done here, release only to satisfy static analyzer
        }
    }
	
	//NSLog(@"sharedEngineRoom is %@", sharedEngineRoom);

	return sharedEngineRoom;
}

+ (id)allocWithZone:(NSZone *)zone
{
    @synchronized(self) {
        if (sharedEngineRoom == nil) {
            return [super allocWithZone:zone];
        }
    }
    return sharedEngineRoom;
}

- (id)init
{
    Class myClass = [self class];
    @synchronized(myClass) {
        if (sharedEngineRoom == nil) {
            if ( (self = [super init] ) ) {
                sharedEngineRoom = self;

				m_standardUserDefaults = [[NSUserDefaults standardUserDefaults] retain];
				m_engineRoomUserDefaults = [[m_standardUserDefaults persistentDomainForName: [[NSBundle bundleForClass: [self class]] bundleIdentifier]] retain];
            }
        }
    }
    return sharedEngineRoom;
}
 
- (id)copyWithZone:(NSZone *)zone { return self; }
 
- (id)retain { return self; }

- (NSUInteger)retainCount { return UINT_MAX; /* denotes an object that cannot be released */ }

- (void)release { /* do nothing */ }

- (id)autorelease { return self; }

- (void) awakeFromNib
{
	if( nil == m_engineRoomController ) {
		m_engineRoomController = [[EngineRoomController sharedEngineRoomController] retain];
		[m_engineRoomController installInMenuItem: engineRoomMenuItem];
	} else {
		// awaking outside of MainMenu nib
	}
}

#pragma mark -
#pragma mark Configuration

- (id) configurationValueForKey: (NSString *) key
{
	id globalValue = [m_engineRoomUserDefaults valueForKey: key];
	return globalValue ? globalValue : [m_standardUserDefaults valueForKey: key];
}

- (NSBundle *) bundle 
{
	return [NSBundle bundleForClass: [self class]];
}

- (NSDictionary *) infoDictionary
{
	return [[self bundle] infoDictionary];
}

- (NSDictionary *) localizedInfoDictionary
{
	return [[self bundle] localizedInfoDictionary];
}


@end

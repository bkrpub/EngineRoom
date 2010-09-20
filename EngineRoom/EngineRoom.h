
#import <EngineRoom/CrossPlatform.h>

#ifdef __ENGINE_ROOM_M__
#define ENGINE_ROOM_GLOBAL(var, value) var = (value)
#else
#define ENGINE_ROOM_GLOBAL(var, value) extern var
#endif

ENGINE_ROOM_GLOBAL(NSString *kEngineRoomInstallMenuUserDefaultsKey, @"engineRoomInstallMenu");

#import <EngineRoom/EngineRoomController.h>

#if TARGET_OS_OSX
#import <EngineRoom/LogPointsWindowController.h>
#import <EngineRoom/ConsoleWindowController.h>
#endif

#import <EngineRoom/logpoints_api.h>
#import <EngineRoom/er_util.h>
#import <EngineRoom/tracer.h>

@interface EngineRoom : NSObject {
	IBOutlet NSMenuItem *engineRoomMenuItem;

	EngineRoomController *m_engineRoomController;

	NSUserDefaults *m_standardUserDefaults;
	NSUserDefaults *m_engineRoomUserDefaults;
}

+ (id) sharedEngineRoom;

- (id) configurationValueForKey: (NSString *) key;

- (NSBundle *) bundle;

- (NSDictionary *) infoDictionary;

@end

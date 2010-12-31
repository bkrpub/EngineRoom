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

- (NSString *) version
{
	return [[self infoDictionary] objectForKey: (id)kCFBundleVersionKey];
}

- (NSDictionary *) localizedInfoDictionary
{
	return [[self bundle] localizedInfoDictionary];
}


@end

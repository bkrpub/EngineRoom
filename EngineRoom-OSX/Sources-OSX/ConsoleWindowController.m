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

#import "ConsoleWindowController.h"
#import "LogPoint.h"
#import "logpoints_bk.h"


@implementation ConsoleWindowController

// all this global stuff is still a huge mess, more demo than anything

NSArrayController *globalMessageArrayController = nil;
LOGPOINT_EMITTER globalSavedEmitter = NULL;

LOGPOINT_EMITTER_DECLARATION(logPointConsoleWindowEmitter)
{	
	if( NULL == logFormat || 0 == *logFormat ) {
		return LOGPOINT_NO;
	}
	
	if( NULL == payload ) {
		payload = "";
	}
	
	char stackBuffer[LOGPOINT_EMITTER_STACKBUFFER];
	size_t wantedSize = strlen(payload) + LOGPOINT_MAX_DECORATION_LENGTH;
	
	char *buffer = logPointAllocateBufferIfNeeded(stackBuffer, sizeof(stackBuffer), wantedSize);
	
	if( NULL != buffer ) {
		logPointFormat(lpp, langSpec1, langSpec2, buffer, wantedSize, NULL, NULL, logFormat, payload);		
		
#if MAINTAINER_WARNINGS
#warning need to check return value 
#endif
		
		NSString *nsMsg = [NSString stringWithUTF8String: buffer];

		NSLog(@"CONSOLE: %s", buffer);
		[globalMessageArrayController addObject: [NSDictionary dictionaryWithObjectsAndKeys: nsMsg, @"message", nil]];
		
		logPointFreeBufferIfNeeded(buffer, stackBuffer);
		
	} else {
		NSLog(@"CONSOLE: logPoints: out of memory - payload: %s", payload);
	}
	
  return LOGPOINT_YES;
}

- (NSMutableArray *) messages
{
	return [[p_messages retain] autorelease];
}

- (void) setMessages: (id) newMessages
{
  if( newMessages != p_messages ) {
    [p_messages autorelease];
    p_messages = [newMessages retain];
  }
}

- (id) init
{
    self = [super initWithWindowNibName: @"ConsoleWindow" owner: self];
    return self;
}

- (void) dealloc
{
  logPointSetEmitter(globalSavedEmitter);
  globalSavedEmitter = NULL;

  [self setMessages: nil];
  globalMessageArrayController = nil;

  [super dealloc];
}


- (void) windowDidLoad
{
	[super windowDidLoad];

	[self setMessages: [NSMutableArray array]];

	globalMessageArrayController = messageArrayController;

	globalSavedEmitter = logPointSetEmitter(logPointConsoleWindowEmitter);
}

- (IBAction) clear: (id) sender
{
	[globalMessageArrayController removeObjects: [globalMessageArrayController arrangedObjects]];
}

@end

//
//  ConsoleWindowController.m
//  EngineRoom
//
//  Created by Bjoern Kriews on 08.03.08.
//  Copyright 2008 Bjoern Kriews. All rights reserved.
//

#import "ConsoleWindowController.h"
#import "LogPoint.h"
#import "logpoints_bk.h"


@implementation ConsoleWindowController

// all this global stuff is still a huge mess, more demo than anything

NSArrayController *globalMessageArrayController = nil;
LOGPOINT_EMITTER globalSavedEmitter = NULL;

LOGPOINT_EMITTER_DECLARATION(logPointConsoleWindowEmitter)
{
  va_list args;
  va_start(args, fmt);

  CFStringRef cfFmt = CFStringCreateWithCStringNoCopy(kCFAllocatorDefault, fmt, kCFStringEncodingUTF8, kCFAllocatorNull /* don't free */);  
  CFStringRef cfMsg = CFStringCreateWithFormatAndArguments(kCFAllocatorDefault, NULL, cfFmt, args);

  NSLog(@"CONSOLE: %@", cfMsg);
  [globalMessageArrayController addObject: [NSDictionary dictionaryWithObjectsAndKeys: (NSString*) cfMsg, @"message", nil]];

  CFRelease(cfMsg);
  CFRelease(cfFmt);

  va_end(args);

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

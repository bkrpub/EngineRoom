//
//  ConsoleWindowController.h
//  EngineRoom
//
//  Created by Bjoern Kriews on 08.03.08.
//  Copyright 2008 Bjoern Kriews. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface ConsoleWindowController : NSWindowController {
	IBOutlet NSArrayController *messageArrayController;
	NSMutableArray *p_messages;
}

- (IBAction) clear: (id) sender;

@end

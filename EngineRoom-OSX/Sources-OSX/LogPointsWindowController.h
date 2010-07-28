//
//  LogPointsWindowController.h
//  EngineRoom
//
//  Created by Bjoern Kriews on 08.03.08.
//  Copyright 2008 Bjoern Kriews. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface LogPointsWindowController : NSWindowController {
		IBOutlet NSTextField *infoField;
		IBOutlet NSTextField *sessionField;
		IBOutlet NSTextField *defaultField;
}

- (void) updateDefaultField;

- (void) presentModalError: (NSError *) error;

- (IBAction) enableLogPointsMatchedBySessionField: (id) sender;
- (IBAction) disableLogPointsMatchedBySessionField: (id) sender;
- (IBAction) enableOnlyLogPointsMatchedBySessionField: (id) sender;

- (IBAction) applyAndSaveDefault: (id) sender;

- (IBAction) enableAll: (id) sender;

- (IBAction) disableAll: (id) sender;


@end

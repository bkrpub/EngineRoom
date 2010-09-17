//
//  LogPointsWindowController.m
//  EngineRoom
//
//  Created by Bjoern Kriews on 08.03.08.
//  Copyright 2008 Bjoern Kriews. All rights reserved.
//

#import "LogPointsWindowController.h"
#import "LogPoint.h"
#import "logpoints_bk.h"

@implementation LogPointsWindowController ( WindowDelegate )

- (void)windowDidBecomeKey:(NSNotification *)notification
{
		[self updateDefaultField];
}

@end

@implementation LogPointsWindowController

- (id) init
{
    self = [super initWithWindowNibName: @"LogPointsWindow" owner: self];
    return self;
}

- (void) updateDefaultField
{
	NSString *filter = [[NSUserDefaults standardUserDefaults] valueForKey: kLogPointFilterUserDefaultsKey];
	[defaultField setStringValue: filter ? filter : @""];
}

- (void) windowDidLoad
{
	[super windowDidLoad];
	[self updateDefaultField];
}

- (void)didPresentErrorWithRecovery:(BOOL)didRecover contextInfo:(void *)contextInfo
{
	// NSLog(@"didPresentErrorWithRecovery: %d ctx: %@", didRecover, contextInfo);
}

- (void) presentModalError: (NSError *) error
{
	[[[self window] firstResponder] presentError: error modalForWindow:[self window] delegate: self didPresentSelector:@selector(didPresentErrorWithRecovery:contextInfo:) contextInfo: nil];
}

- (IBAction) enableAll: (id) sender
{
	[LogPoint makeAllLogPointsPerformSelector: @selector(activate)];
}

- (IBAction) disableAll: (id) sender
{
	[LogPoint makeAllLogPointsPerformSelector: @selector(deactivate)];
}


- (IBAction) enableLogPointsMatchedBySessionField: (id) sender
{
	NSError *error = nil;
	if( 0 > [LogPoint makeLogPointsMatchingFilterString: [sessionField stringValue] performSelector: @selector(activate) error: &error] ) {
		[self presentModalError: error];
	}
}

- (IBAction) disableLogPointsMatchedBySessionField: (id) sender
{
	NSError *error = nil;
	if( 0 > [LogPoint makeLogPointsMatchingFilterString: [sessionField stringValue] performSelector: @selector(deactivate) error: &error] ) {
		[self presentModalError: error];		
	}
}

- (IBAction) enableOnlyLogPointsMatchedBySessionField: (id) sender
{
	NSError *error = nil;
	if( 0 > [LogPoint enableOnlyLogPointsMatchingFilterString: [sessionField stringValue] error: &error] ) {
		[self presentModalError: error];		
	}
}

- (IBAction) applyAndSaveDefault: (id) sender
{
	NSError *error = nil;
	NSString *filter = [defaultField stringValue];
	if( 0 > [LogPoint enableOnlyLogPointsMatchingFilterString: filter error: &error] ) {
		[self presentModalError: error];		
	} else {
		[[NSUserDefaults standardUserDefaults] setValue: filter forKey: kLogPointFilterUserDefaultsKey];
		[[NSUserDefaults standardUserDefaults] synchronize];
	}
}



@end

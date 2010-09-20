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

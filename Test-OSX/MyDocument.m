//
//  MyDocument.m
//  EngineRoomTest
//
//  Created by Bjoern Kriews on 08.03.08.
//  Copyright Bjoern Kriews 2008 . All rights reserved.
//

#import "MyDocument.h"
#import <EngineRoom/EngineRoom.h>
#import <EngineRoom/logpoints_bk.h>


@implementation MyDocument

- (IBAction) generateWarning: (id) sender
{
	lpwarning("interface", "please do not press this (%@) again\n%@", sender, tracerBacktraceAsString(0));
}

- (IBAction) takeTestValueFrom: (id) sender
{
	lpdebug("action", "sender: %@", sender);

	/*dbug([sender frame]);*/

	NSString *string = [sender stringValue];

	if( lpdebugswitch("action,expandInput", "trying to expand %@", string) ) {
		if( [string isEqualToString: @"*"] ) {
			[sender setStringValue: @"42"];
		}
	}

	int length = [[sender stringValue] length];

	if( length ) {
		dbug(length);
		dbug([sender doubleValue]);
		dbug( NSMakeSize(length, length) );
	} else {
		lperror("interface,entry", "empty value from %@", sender);
	}


}

- (id)init
{
    self = [super init];
    if (self) {
    
        // Add your subclass-specific initialization here.
        // If an error occurs here, send a [self release] message and return nil.
    
    }

    dbug_return(self);
}

- (NSString *)windowNibName
{
    dbug_return(@"MyDocument");
}

- (void)windowControllerDidLoadNib:(NSWindowController *) aController
{
    [super windowControllerDidLoadNib:aController];
    // Add any code here that needs to be executed once the windowController has loaded the document's window.
}

- (NSData *)dataOfType:(NSString *)typeName error:(NSError **)outError
{
    // Insert code here to write your document to data of the specified type. If the given outError != NULL, ensure that you set *outError when returning nil.

    // You can also choose to override -fileWrapperOfType:error:, -writeToURL:ofType:error:, or -writeToURL:ofType:forSaveOperation:originalContentsURL:error: instead.

    // For applications targeted for Panther or earlier systems, you should use the deprecated API -dataRepresentationOfType:. In this case you can also choose to override -fileWrapperRepresentationOfType: or -writeToFile:ofType: instead.

    if ( outError != NULL ) {
		*outError = [NSError errorWithDomain:NSOSStatusErrorDomain code:unimpErr userInfo:NULL];
	}
	return nil;
}

- (BOOL)readFromData:(NSData *)data ofType:(NSString *)typeName error:(NSError **)outError
{
    // Insert code here to read your document from the given data of the specified type.  If the given outError != NULL, ensure that you set *outError when returning NO.

    // You can also choose to override -readFromFileWrapper:ofType:error: or -readFromURL:ofType:error: instead. 
    
    // For applications targeted for Panther or earlier systems, you should use the deprecated API -loadDataRepresentation:ofType. In this case you can also choose to override -readFromFile:ofType: or -loadFileWrapperRepresentation:ofType: instead.
    
    if ( outError != NULL ) {
		*outError = [NSError errorWithDomain:NSOSStatusErrorDomain code:unimpErr userInfo:NULL];
	}
    return YES;
}

@end

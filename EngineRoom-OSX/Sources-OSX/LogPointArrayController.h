/* LogPointArrayController */

#import <Cocoa/Cocoa.h>

@interface LogPointArrayController : NSArrayController
{
}

- (void)tableView:(NSTableView *)aTableView willDisplayCell:(id)aCell forTableColumn:(NSTableColumn *)aTableColumn row:(int)rowIndex;

@end

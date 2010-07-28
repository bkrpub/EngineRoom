#import "LogPointArrayController.h"
#import "LogPoint.h"

@implementation LogPointArrayController

- (void)tableView:(NSTableView *)aTableView willDisplayCell:(id)aCell forTableColumn:(NSTableColumn *)aTableColumn row:(int)rowIndex
{
    (void) aTableView;
    (void) aTableColumn;
    (void) rowIndex;
    
    if( NO == [aCell isKindOfClass: [NSButtonCell class]] )
        return;

    // LogPoint *logPoint = [[self arrangedObjects] objectAtIndex: rowIndex];
    // [aCell setTitle: [logPoint stateSummary]];
    
    //[aCell setShowsStateBy: [aCell showsStateBy] | NSContentsCellMask];
}

@end


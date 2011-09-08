
#import "Convenience.h"

#import "NSBundle_ERResourceExtensions.h"

#import "NSPropertyListSerialization_ERBackPortExtensions.h"


@implementation NSBundle (ERResourceExtensions)

- (NSData *) er_dataResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) dataOptions error: (NSError **) outError 
{
	ER_PRECONDITION_NSERROR_RETURN_NIL(name != nil, outError);
	
	NSURL *resourceURL = [self resourceURL];
	
	NSURL *URL = [resourceURL URLByAppendingPathComponent: name];

	if( nil != type ) {
		URL = [URL URLByAppendingPathExtension: type];	
	}
    
	return [NSData dataWithContentsOfURL: URL options: dataOptions error: outError];
}

- (id) er_propertyListResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) plistOptions error: (NSError **) outError 
{
	ER_PRECONDITION_NSERROR_RETURN_NIL(name != nil, outError);
	
	NSData *data = [self er_dataResource: name ofType: type options: 0 error: outError];
	return data ? [NSPropertyListSerialization er_propertyListWithData: data options: plistOptions error: outError] : nil;
}
	
@end

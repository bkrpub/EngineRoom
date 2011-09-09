
#import "Convenience.h"

#import "NSBundle_ERExtensions.h"

#import "NSPropertyListSerialization_ERExtensions.h"


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

@implementation NSBundle (ERInfoDictionaryExtensions)

- (NSString *) er_machineReadableVersionString
{
    NSString *shortVersion = [self objectForInfoDictionaryKey: @"CFBundleShortVersionString"];
    NSString *version = [self objectForInfoDictionaryKey: (id)kCFBundleVersionKey];
    NSString *name = [self objectForInfoDictionaryKey: (id)kCFBundleIdentifierKey];
   
   return [NSString stringWithFormat: @"%@%s%@%s%@", 
           name, shortVersion ? "-" : "", shortVersion ?: @"", version ? "-" : "", version ?: @""];
}

- (NSString *) er_humanReadableVersionString
{
    NSString *shortVersion = [self objectForInfoDictionaryKey: @"CFBundleShortVersionString"];
    NSString *version = [self objectForInfoDictionaryKey: (id)kCFBundleVersionKey];
    NSString *name = [self objectForInfoDictionaryKey: (id)kCFBundleNameKey];
    
   return [NSString stringWithFormat: @"%@%s%@%s%@%s", 
           name, shortVersion ? " " : "", shortVersion ?: @"", version ? " (" : "", version ?: @"", version ? ")" : ""];
}

@end

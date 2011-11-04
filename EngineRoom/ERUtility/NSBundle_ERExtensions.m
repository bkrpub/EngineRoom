
#import "Convenience.h"

#import <EngineRoom/NSBundle_ERExtensions.h>

#import <EngineRoom/NSPropertyListSerialization_ERExtensions.h>

NSString *kERBundleBuildConfiguration = @"ERBundleBuildConfiguration";

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
    NSString *shortVersion = [self objectForInfoDictionaryKey: @"CFBundleShortVersionString"] ?: (id)@"noShortVersion";
    NSString *version = [self objectForInfoDictionaryKey: (id)kCFBundleVersionKey] ?: (id)@"noVersion";
    NSString *name = [self objectForInfoDictionaryKey: (id)kCFBundleNameKey] ?: (id)@"noName";
    
       NSString *config = [self objectForInfoDictionaryKey: (id)kERBundleBuildConfiguration];
    
   return [NSString stringWithFormat: @"%@-%@%s%@-%@", 
           name, 
           shortVersion,
           config ? "-" : "", config ?: @"",
           version
           ];
}

- (NSString *) er_humanReadableVersionString
{
    NSString *shortVersion = [self objectForInfoDictionaryKey: @"CFBundleShortVersionString"] ?: (id)@"noShortVersion";
    NSString *version = [self objectForInfoDictionaryKey: (id)kCFBundleVersionKey] ?: (id)@"noVersion";
    NSString *name = [self objectForInfoDictionaryKey: (id)kCFBundleNameKey] ?: (id)@"noName";
    
    NSString *config = [self objectForInfoDictionaryKey: (id)kERBundleBuildConfiguration];
    
   return [NSString stringWithFormat: @"%@ %@ (%@%s%@)", 
           name, 
           shortVersion,
           config ?: @"", config ? " " : "",
           version
           ];
}

@end

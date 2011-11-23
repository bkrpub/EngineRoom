
#import "Convenience.h"

#import <EngineRoom/NSBundle_ERExtensions.h>

#import <EngineRoom/NSPropertyListSerialization_ERExtensions.h>

NSString *kERBundleBuildConfiguration = @"ERBundleBuildConfiguration";

@implementation NSBundle (ERResourceExtensions)

- (NSURL *) er_URLForResource: (NSString *) name withExtension: (NSString *) extension error: (NSError **) outError
{
    ER_PRECONDITION_NSERROR_RETURN_NIL(name != nil, outError);

    NSURL *URL = [self URLForResource: name withExtension: extension ?: @""];
    
    ER_CHECK_NSERROR_REASON_RETURN_NIL(nil != URL, outError, NSPOSIXErrorDomain, ENOENT, @"NO_SUCH_RESOURCE: %@%@%@", name, extension ? @"." : @"", extension ?: @"");
    
    return URL;
}

- (NSData *) er_dataResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) dataOptions error: (NSError **) outError 
{
    NSURL *URL = [self er_URLForResource: name withExtension: type error: outError];

    if( nil == URL ) {
        return nil;
    }
    
	return [NSData dataWithContentsOfURL: URL options: dataOptions error: outError];
}

- (id) er_propertyListResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) plistOptions error: (NSError **) outError 
{	
	NSData *data = [self er_dataResource: name ofType: type options: 0 error: outError];
	return data ? [NSPropertyListSerialization er_propertyListWithData: data options: plistOptions error: outError] : nil;
}

- (NSString *) er_stringResource: (NSString *) name ofType: (NSString *) type encoding: (NSStringEncoding) encoding error: (NSError **) outError
{
    NSURL *URL = [self er_URLForResource: name withExtension: type error: outError];
    NSString *string = URL ? [NSString stringWithContentsOfURL: URL encoding: encoding error: outError] : nil;
    return string;
}

- (NSString *) er_stringResource: (NSString *) name ofType: (NSString *) type error: (NSError **) outError
{
    NSURL *URL = [self er_URLForResource: name withExtension: type error: outError];
    NSString *string = URL ? [NSString stringWithContentsOfURL: URL usedEncoding: nil error: outError] : nil;
    return string;
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

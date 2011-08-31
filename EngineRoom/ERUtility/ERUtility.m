//
//  ERUtility.m
//  EngineRoom-OSX
//
//  Created by Bjoern Kriews on 2/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <EngineRoom/ERUtility.h>

#import <EngineRoom/Convenience.h>
#import <EngineRoom/logpoints_default.h>

NSString *ERUtilityBundleIdentifierWorkspace = @"com.apple.finder";

NSString *ERUtilityOptionExportOpenWithBundleIdentifier = @"ERUtilityOptionExportOpenWithBundleIdentifier";
NSString *ERUtilityOptionExportBaseTypesAsPropertyList = @"ERUtilityOptionExportBaseTypesAsPropertyList";
NSString *ERUtilityOptionExportDateFormat = @"ERUtilityOptionExportDateFormat";

/* 
 * helper function to make ER_DICT use the more natural key, value order 
 * from the blog of Mike Ash
 */
NSDictionary *ERDictionaryWithKeysAndObjects(id *array, NSUInteger count)
{
	id keys[count];
	id objs[count];
	
	for(NSUInteger i = 0; i < count; i++)
	{
		keys[i] = array[i * 2];
		objs[i] = array[i * 2 + 1];
	}
	
	return [NSDictionary dictionaryWithObjects: objs forKeys: keys count: count];
}

@implementation ERUtility

+ (NSString *) XMLCompatibleUUIDString
{
    NSString *UUIDString = [self UUIDString];
    return UUIDString ? [@"U" stringByAppendingString: UUIDString] : nil;
}

+ (NSString *) UUIDString;
{
	CFUUIDRef cfUUID = CFUUIDCreate(kCFAllocatorDefault);
	NSString *nsUUIDString = nil;
	
	if( NULL != cfUUID ) {
		
		CFStringRef cfUUIDString = CFUUIDCreateString(kCFAllocatorDefault, cfUUID);
		
		if( NULL != cfUUIDString ) {
			
			nsUUIDString = [NSString stringWithString: (NSString *) cfUUIDString];
			
			CFRelease(cfUUIDString);
		}
		
		CFRelease(cfUUID);
	}
	
	return nsUUIDString;
}


+ (NSString *) timestampWithDateFormat: (NSString *) dateFormat
{
	NSDateFormatter *formatter = [[[NSDateFormatter alloc] init] autorelease];
	[formatter setDateFormat: dateFormat ? dateFormat : @"yyyy-MM-dd_HH_mm_ss_SSS"];
	return [formatter stringFromDate: [NSDate date]];
}

+ (NSURL *) URLForResourceWithBaseURL: (NSURL *) baseURL basename: (NSString *) basename type: (NSString *) type dateFormat: (NSString *) dateFormat
{
	if( nil == baseURL ) {
		baseURL = [NSURL fileURLWithPath: NSTemporaryDirectory()];
	}
	
	NSURL *URL = [baseURL URLByAppendingPathComponent: [NSString stringWithFormat:@"%@%@%@.%@", 
														basename, 
														dateFormat ? @"-" : @"", 
														dateFormat ? [self timestampWithDateFormat: [dateFormat length] ? dateFormat : nil] : @"", 
														type]];
	return URL;
}

+ (NSURL *) exportPropertyListItem: (id) item baseURL: (NSURL *) baseURL basename: (NSString *) basename type: (NSString *) type options: (NSDictionary *) options error: (NSError **) outError
{
	NSNumber *baseTypesAsPropertyList = [options valueForKey: ERUtilityOptionExportBaseTypesAsPropertyList];
	NSString *dateFormat = [options valueForKey: ERUtilityOptionExportDateFormat];

	NSURL *URL= [self URLForResourceWithBaseURL: baseURL basename: basename type: type dateFormat: dateFormat];
	
	BOOL success = NO;
	
	NSData *data = nil;
	
	if( NO == [baseTypesAsPropertyList boolValue] ) {
		if( [item isKindOfClass: [NSData class]] ) {
			data = item;
		} else {	
			if( [item isKindOfClass: [NSString class]] || 
			    [item isKindOfClass: [NSNumber class]] || 
			    [item isKindOfClass: [NSDate class]] ) {
				data = [(NSString *)item dataUsingEncoding: NSUTF8StringEncoding allowLossyConversion: NO]; //may return nil
			}
		}
	}
	
	if( nil == data ) {
		data = [NSPropertyListSerialization dataWithPropertyList: item format: NSPropertyListXMLFormat_v1_0 options: 0 error: outError];
	}
	
	if( data ) {
		success = [data writeToURL: URL options: NSDataWritingAtomic error: outError];

#if TARGET_OS_OSX
		NSString *bundleIdentifier = [options valueForKey: ERUtilityOptionExportOpenWithBundleIdentifier];
			
		if( YES == success && nil != bundleIdentifier ) {
			NSWorkspace *workspace = [NSWorkspace sharedWorkspace];
			
			NSArray *URLs = [NSArray arrayWithObject: URL];

			lpdebug(URL);
			
			success = [workspace openURLs:URLs withAppBundleIdentifier: bundleIdentifier options: NSWorkspaceLaunchDefault additionalEventParamDescriptor: nil launchIdentifiers: nil];
			
			if( NO == success ) { 
				ER_SET_NSERROR_REASON( outError, NSPOSIXErrorDomain, EINVAL, @"cantOpenURLWithWorkspace: %@", URL);
			}
		} 
#endif
/* TARGET_OS_OSX */
	}
	
	return success ? URL : nil;
}

#if 0

+ (NSURL *) temporaryURLForPropertyListItem: (id) plist basename: (NSString *) basename type: (NSString *) type dateFormat: (NSString *) dateFormat openWithBundleIdentifier: (NSString *) bundleIdentifier;
{	
	NSError *error = nil;
	NSURL *URL = [self temporaryURLForPropertyListItem: plist toBaseURL: nil basename: basename type: type dateFormat: dateFormat baseTypesRaw: YES openWithBundleIdentifier: bundleIdentifier error: &error];
	
	if( nil == URL ) {
		[NSApp presentError: error];
	}
	
	return URL;
}


- (IBAction) pluginActionDumpStageAsPlist: (id) sender
{
	NSDictionary *dump = [[self stage] dictionaryRepresentationWithOptions: nil];
	
	[self dumpPropertyListItem: dump basename: @"stage" type: @"plist" openWithBundleIdentifier: @"com.apple.finder"];
}

- (IBAction) pluginActionDumpStageAsDot: (id) sender
{
	NSString *dot = [[self stage] dotWithOptions: nil];
	
	[self dumpPropertyListItem: dot basename: @"stage" type: @"gv" openWithBundleIdentifier: @"com.apple.finder"];
}

- (IBAction) pluginActionDumpManagedObjectContextAsPlist: (id) sender
{
	NSArray *objects = [[NSApp valueForKeyPath: @"delegate.currentDocument.managedObjectContext.registeredObjects"] allObjects];
	
	NSArray *dump = [NSManagedObject dictionaryRepresentationsOfObjects: objects options: nil];
	
	[self dumpPropertyListItem: dump basename: @"registeredObjects" type: @"plist" openWithBundleIdentifier: @"com.apple.finder"];
}

- (IBAction) pluginActionDumpManagedObjectContextAsDot: (id) sender
{
	NSArray *objects = [[NSApp valueForKeyPath: @"delegate.currentDocument.managedObjectContext.registeredObjects"] allObjects];
	
	NSMutableDictionary *visitedObjects = [NSMutableDictionary dictionary];
	NSCountedSet *countedTypes = [NSCountedSet set];
	NSMutableString *dot = [NSMutableString stringWithString: @"digraph G {\nrankdir = TB;\n"];
	
	for(NSManagedObject *obj in objects) {
		[obj dotWithOptions: nil visitedObjects: visitedObjects countedTypes: countedTypes dot: dot];
	}
	
	[dot appendString: @"}\n"];
	
	[self dumpPropertyListItem: dot basename: @"registeredObjects" type: @"gv" openWithBundleIdentifier: @"com.apple.finder"];
}

#endif
@end

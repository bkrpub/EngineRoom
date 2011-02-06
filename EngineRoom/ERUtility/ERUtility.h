//
//  ERUtility.h
//  EngineRoom-OSX
//
//  Created by Bjoern Kriews on 2/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <EngineRoom/CrossPlatform.h>

// categories, all methods prefixed with er_
#import <EngineRoom/NSPropertyListSerialization_ERBackPortExtensions.h>
#import <EngineRoom/NSBundle_ERResourceExtensions.h>

extern NSString *ERUtilityBundleIdentifierWorkspace;

extern NSString *ERUtilityOptionExportOpenWithBundleIdentifier;
extern NSString *ERUtilityOptionExportBaseTypesAsPropertyList;
extern NSString *ERUtilityOptionExportDateFormat; 

extern NSDictionary *ERDictionaryWithKeysAndObjects(id *array, NSUInteger count);


@interface ERUtility : NSObject {

}

+ (NSString *) UUIDString;

+ (NSURL *) exportPropertyListItem: (id) item baseURL: (NSURL *) baseURL basename: (NSString *) basename type: (NSString *) type options: (NSDictionary *) options error: (NSError **) outError;



@end

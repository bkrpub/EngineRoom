//
//  ERBundleExtensions.h
//  EngineRoom-OSX
//
//  Created by Bjoern Kriews on 9/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSObject (ERBundleExtensions)

+ (NSBundle *) er_classBundle;
- (NSBundle *) er_classBundle;

+ (NSString *) er_pathForClassResource: (NSString *) name ofType: (NSString *) type;
- (NSString *) er_pathForClassResource: (NSString *) name ofType: (NSString *) type;

+ (NSString *) er_pathForMainResource: (NSString *) name ofType: (NSString *) type;
- (NSString *) er_pathForMainResource: (NSString *) name ofType: (NSString *) type;

+ (NSString *) er_pathForMainOrClassResource: (NSString *) name ofType: (NSString *) type;
- (NSString *) er_pathForMainOrClassResource: (NSString *) name ofType: (NSString *) type;


- (NSData *) er_classDataResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) dataOptions error: (NSError **) outError;

- (id) er_classPropertyListResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) plistOptions error: (NSError **) outError;

- (NSData *) er_mainOrClassDataResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) dataOptions error: (NSError **) outError;

- (id) er_mainOrClassPropertyListResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) plistOptions error: (NSError **) outError;

@end

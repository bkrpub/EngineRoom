//
//  ERBundleExtensions.m
//  EngineRoom-OSX
//
//  Created by Bjoern Kriews on 9/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "NSObject_ERBundleExtensions.h"
#import "NSBundle_ERResourceExtensions.h"

@implementation NSObject (ERBundleExtensions)

#if 0
+ (NSBundle *) er_classBundle
{
    return [NSBundle bundleForClass: self];
}

+ (NSString *) er_pathForClassResource: (NSString *) name ofType: (NSString *) type
{
    // should walk the inheritance tree
    return [[self er_classBundle] pathForResource: name ofType: type];
}

+ (NSString *) pathForMainResource: (NSString *) name ofType: (NSString *) type
{
    return [[NSBundle mainBundle] pathForResource: name ofType: type];
}

+ (NSString *) er_pathForMainOrClassResource: (NSString *) name ofType: (NSString *) type
{
    NSString *path = [self er_pathForMainResource: name ofType: type];
    return path ? path : [self er_pathForClassResource: name ofType: type];
}

#endif

- (NSBundle *) er_classBundle
{
    return [NSBundle bundleForClass: [self class]];
}

- (NSString *) er_pathForClassResource: (NSString *) name ofType: (NSString *) type
{
    // should walk the inheritance tree
    return [[self er_classBundle] pathForResource: name ofType: type];
}

- (NSString *) er_pathForMainResource: (NSString *) name ofType: (NSString *) type
{
    return [[NSBundle mainBundle] pathForResource: name ofType: type];
}

- (NSString *) pathForMainOrClassResource: (NSString *) name ofType: (NSString *) type
{
    NSString *path = [self er_pathForMainResource: name ofType: type];
    return path ? path : [self er_pathForClassResource: name ofType: type];
}

- (NSData *) er_classDataResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) dataOptions error: (NSError **) outError
{
    return [[self er_classBundle] er_dataResource: name ofType: type options: dataOptions error: outError];
}

- (id) er_classPropertyListResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) plistOptions error: (NSError **) outError
{
    return [[self er_classBundle] er_propertyListResource: name ofType: type options: plistOptions error: outError];
}

- (NSData *) er_mainOrClassDataResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) dataOptions error: (NSError **) outError
{
    return [[NSBundle mainBundle] er_dataResource: name ofType: type options: dataOptions error:outError] ?:
    [[self er_classBundle] er_dataResource: name ofType: type options: dataOptions error:outError];
}

- (id) er_mainOrClassPropertyListResource: (NSString *) name ofType: (NSString *) type options: (NSUInteger) plistOptions error: (NSError **) outError
{
    return [[NSBundle mainBundle] er_propertyListResource: name ofType: type options: plistOptions error:outError] ?:
    [[self er_classBundle] er_propertyListResource: name ofType: type options: plistOptions error:outError];
}

@end

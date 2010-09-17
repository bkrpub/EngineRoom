//
//  $Id: LogPoint.h 773 2009-02-24 00:45:22Z bkr $
//
//  Copyright (c) 2007 Bjoern Kriews
//

#import <Foundation/Foundation.h>

#import "logpoints.h"

extern NSString *kLogPointFilterUserDefaultsKey;
extern NSString *kLogPointDumpUserDefaultsKey;

@interface LogPoint : NSObject
{
    @private

    LOGPOINT *raw;
    NSArray  *cachedKeys;

    size_t kindLength;
    size_t keysLength;
    size_t functionLength;
    size_t fileLength; 
    size_t labelLength; 
    size_t formatInfoLength; 

    size_t imageLength;
    const char *imageFileName;
    size_t imageFileNameLength;

    const char *fileName;
    size_t fileNameLength;

    unichar methodType;

    const char *className;
    size_t classNameLength;

    const char *selectorName;
    size_t selectorNameLength;
}

// called automagically by a constructor function
+ (BOOL) setup;

+ (lp_return_t) setErrorPtr: (NSError **) outError withCode: (lp_return_t) code userInfo: (NSDictionary *) userInfo;

+ (lp_return_t) makeAllLogPointsPerformSelector: (SEL) sel;

+ (lp_return_t) makeLogPointsMatchingFilterString: (NSString *) filter performSelector: (SEL) sel error: (NSError **) outError;
+ (lp_return_t) enableOnlyLogPointsMatchingFilterString: (NSString *) filter error: (NSError **) outError;

+ (lp_return_t) makeLogPointsMatchingPredicate: (NSPredicate *) predicate performSelector: (SEL) sel error: (NSError **) outError;
+ (lp_return_t) enableOnlyLogPointsMatchingPredicate: (NSPredicate *) predicate error: (NSError **) outError;

+ (NSPredicate *) predicateFromTextualRepresentation: (id) textual error: (NSError **) outError;

+ (NSArray *) sharedLogPoints;

// to be able to use an instance in IB for binding
- (NSArray *) sharedLogPoints;

- (id) initWithRawPointer: (void *) rawPointer; 
- (void *) rawPointer;

- (NSString *) kind;

- (NSString *) commaSeparatedKeys;
- (NSArray *) keys;

- (NSString *) function;

- (unichar) methodType;
- (NSString *) methodTypeAsString;
- (NSString *) className;
- (NSString *) selectorName;
- (NSString *) selectorNameWithTypePrefix;

- (NSString *) sourcePath;
- (NSString *) sourceFileName;

- (NSString *) binaryPath;
- (NSString *) binaryFileName;

- (NSInteger) line;

- (NSInteger) count;
- (void) setCount: (int) newCount;

- (void *) address;
- (NSString *) addressAsString;

- (NSString *) formatInfo;
- (NSString *) label;

- (void) activate;
- (void) deactivate;

- (BOOL) isActive;
- (void) setActive: (BOOL) flag;

- (BOOL) isHard;
- (void) setHard: (BOOL) flag;

- (BOOL) isInDynamicCode;
- (void) setInDynamicCode: (BOOL) flag;

- (BOOL) isBroken;
- (void) setBroken: (BOOL) flag;

@end

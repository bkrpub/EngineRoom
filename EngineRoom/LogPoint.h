/*
 This file is part of EngineRoom, Copyright (c) 2007-2010 Bjoern Kriews, Hamburg - All rights reserved.

 Redistribution and use in source and binary forms, with or without modification,
 are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

 Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer
 in the documentation and/or other materials provided with the distribution.

 Neither the name of the author nor the names of its contributors may be used to endorse or promote products derived from this
 software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#import <Foundation/Foundation.h>

#import "logpoints_api.h"

extern NSString *kLogPointFilterUserDefaultsKey;
extern NSString *kLogPointFilterVersionUserDefaultsKey;

extern NSString *kLogPointDumpUserDefaultsKey;
extern NSString *kLogPointDumpFormatUserDefaultsKey;
extern NSString *kLogPointLogFormatUserDefaultsKey;

@interface LogPoint : NSObject
{
    @private

    LOGPOINT *raw;
    NSArray  *cachedKeys;

    size_t kindLength;
    size_t keysLength;
    size_t symbolNameLength;
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

// called automagically by a constructor symbolName
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

- (NSString *) symbolName;

- (unichar) methodType;
- (NSString *) methodTypeAsString;
- (NSString *) className;
- (NSString *) selectorName;
- (NSString *) selectorNameWithTypePrefix;
- (NSString *) symbolNameOrSelectorName;

- (NSString *) symbolNameOrSelectorNameForDisplay;
- (NSString *) symbolNameOrSelectorNameWithTypePrefixForDisplay;

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

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

#import "LogPoint.h"

#import "logpoints_bk.h"

NSString *kLogPointFilterUserDefaultsKey = @"logPointFilter";
NSString *kLogPointDumpUserDefaultsKey = @"logPointDump";

#if ! MAINTAINER_WARNINGS
#undef lpkwarningf
#define lpkwarningf(keys, fmt, ...) /**/
#endif

#import <stdlib.h>

#define NSSTRINGWRAPPER(bytes,len) \
[[[NSString alloc] initWithBytesNoCopy: (void*)(bytes) length: (len) encoding: NSUTF8StringEncoding freeWhenDone: NO] autorelease]

#define SIMPLEWRAPPER(what) ({ \
    if( what##Length == 0 && raw->what != NULL ) { \
        what##Length = strlen( raw->what ); \
    } \
    what##Length ? NSSTRINGWRAPPER(raw->what, what##Length) : nil; })

@implementation LogPoint

static NSMutableArray *_sharedLogPoints = nil;
static BOOL setupDone = NO;

void __attribute__ ((constructor)) logPointConstructor(void)
{
	[LogPoint setup];
}

lp_return_t logPointCollector(LOGPOINT *lp, void *userInfo)
{
	LogPoint *point = [[(Class) userInfo alloc] initWithRawPointer: lp];
    [_sharedLogPoints addObject: point];
    [point release];

    return LOGPOINT_RETURN_OK;
}

+ (BOOL) setup
{
	if( setupDone ) 
		return YES;
	else
		setupDone = YES;

	BOOL ret = YES;


	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    id defaults = [NSUserDefaults standardUserDefaults];
        
    NSString *filter = [defaults valueForKey: kLogPointFilterUserDefaultsKey];
    BOOL dump = [defaults boolForKey: kLogPointDumpUserDefaultsKey];

	if( YES == dump ) {
		logPointDumpAll();
	}

	if( filter ) {	
		NSLog(@"LogPoint filter: %@", filter);
		
		NSError *error = nil;
		if( 0 > [self enableOnlyLogPointsMatchingFilterString: filter error: &error] ) {
			NSLog(@"could not compile LogPoint filter '%@' error: %@", filter, error);
			ret = NO;		
		}
	}

	[pool release];

	return ret;
}

+ (lp_return_t) setErrorPtr: (NSError **) outError withCode: (lp_return_t) code userInfo: (NSDictionary *) userInfo
{
	if( outError ) {
		if( nil == [userInfo valueForKey: NSLocalizedDescriptionKey] ) {
			userInfo = userInfo ? [[userInfo mutableCopy] autorelease]: [NSMutableDictionary dictionary];
			[userInfo setValue: [NSString stringWithUTF8String: logPointReturnString(code)] forKey: NSLocalizedDescriptionKey];
		}
		
		*outError = [NSError errorWithDomain: [[NSBundle bundleForClass: self] bundleIdentifier] code: code userInfo: userInfo];
	}

	return code;
}

+ (lp_return_t) makeAllLogPointsPerformSelector: (SEL) sel
{
    NSArray *logPoints = [self sharedLogPoints];
    [logPoints makeObjectsPerformSelector: sel];
    return (lp_return_t) [logPoints count];
}

+ (lp_return_t) makeLogPointsMatchingFilterString: (NSString *) filter performSelector: (SEL) sel error: (NSError **) outError
{
	NSPredicate *predicate = [self predicateFromTextualRepresentation: filter error: outError];
	return predicate ? [self makeLogPointsMatchingPredicate: predicate performSelector: sel error: outError] : LOGPOINT_RETURN_BAD_FILTER;		
}

+ (lp_return_t) enableOnlyLogPointsMatchingFilterString: (NSString *) filter error: (NSError **) outError
{
	NSPredicate *predicate = [self predicateFromTextualRepresentation: filter error: outError];
	return predicate ? [self enableOnlyLogPointsMatchingPredicate: predicate error: outError] : LOGPOINT_RETURN_BAD_FILTER;
}

+ (lp_return_t) makeLogPointsMatchingPredicate: (NSPredicate *) predicate performSelector: (SEL) sel error: (NSError **) outError
{
	if( outError )
		*outError = nil;

	if( nil == predicate ) {
		return [self setErrorPtr: outError withCode: LOGPOINT_RETURN_BAD_FILTER userInfo: nil];
	}

    NSArray *logPoints = [self sharedLogPoints];
    
    NSArray *matching = [logPoints filteredArrayUsingPredicate: predicate];
    
    [matching makeObjectsPerformSelector: sel];

    return [matching count];
}

+ (lp_return_t) enableOnlyLogPointsMatchingPredicate: (NSPredicate *) predicate error: (NSError **) outError
{
    NSPredicate *filteredPredicate = [NSPredicate predicateWithFormat: @"isHard = FALSE"];
    lp_return_t filtered __attribute__((unused)) = [self makeLogPointsMatchingPredicate: filteredPredicate performSelector: @selector(deactivate) error: outError];

	if( nil != predicate ) {
		lp_return_t activated = [self makeLogPointsMatchingPredicate: predicate performSelector: @selector(activate) error: outError];
		lpkwarningf("filtering", "activated %u of %u filtered logpoints for '%@'", activated, filtered, [predicate predicateFormat]);
		return activated;
	} else {
		lpkwarningf("filtering", "no predicate given");
		return LOGPOINT_RETURN_BAD_FILTER;
	}
	
	
}

+ (NSPredicate *) predicateFromTextualRepresentation: (NSString *) textualRep error: (NSError **) outError
{
    if( textualRep == nil ) {
		[self setErrorPtr: outError withCode: LOGPOINT_RETURN_BAD_FILTER userInfo: nil];
        return nil;
	}
    
    if( ! [textualRep respondsToSelector: @selector(length)] || ! [textualRep respondsToSelector: @selector(rangeOfString:)] ) {
        lpkwarningf("filtering", "textual representation '%@' does not respond to length:, rangeOfString: - ignoring", textualRep);
		[self setErrorPtr: outError withCode: LOGPOINT_RETURN_BAD_FILTER userInfo: nil];
        return nil;
    }
 
	if( [textualRep rangeOfString: @"%"].location != NSNotFound ) {
		lpkwarningf("filtering", "textual representation '%@' contains a %% character - not supported - ignoring", textual);
		[self setErrorPtr: outError withCode: LOGPOINT_RETURN_BAD_FILTER userInfo: 
		 [NSDictionary dictionaryWithObject: NSLocalizedString(@"% not supported in filter string - ignored", @"") forKey: NSLocalizedFailureReasonErrorKey]];
		return nil;
	} 
 
 #if MAINTAINER_WARNINGS
#warning BK: move this to arrays
#endif	
	NSMutableString *finalTextual = [NSMutableString string];

	NSEnumerator *repEnum = [[textualRep componentsSeparatedByString: @";"] objectEnumerator];
	
	NSString *textual;
	
	while( nil != ( textual = [repEnum nextObject] ) ) {
	
		textual = [textual stringByTrimmingCharactersInSet: [NSCharacterSet whitespaceAndNewlineCharacterSet]];
		
		if( [textual length] > 1 ) {
			unichar firstChar = [textual characterAtIndex: 0];
			NSString *format = nil;
		
			switch( firstChar ) {
				case '#':
					format = @"keys CONTAINS '%@'";
					break;
				case '=':
					format = @"kind CONTAINS '%@'";
					break;
				case ':':
					format = @"functionOrSelectorName BEGINSWITH '%@'";
					break;
				case '@':
					format = @"className BEGINSWITH '%@'";
					break;
				case '?':
					format = @"formatInfo CONTAINS '%@'";
					break;
				case '/':
					format = @"description CONTAINS '%@'";
					break;
				case '*':
					format = @"binaryFileName BEGINSWITH '%@'";
					break;

			}
			
			if( format ) {
				textual = [NSString stringWithFormat: format, [textual substringFromIndex: 1]];
			}
		}
		
		
		if( 0 == [textual length] ) {
			lpkwarningf("filtering", "interpreting empty string as false");
			textual = @"FALSEPREDICATE";
		}                    
		
		if( [textual isEqualToString: @"*"] ) {
			lpkwarningf("filtering", "interpreting * string as true");
			textual = @"TRUEPREDICATE";
		}                    	 
		

		[finalTextual appendFormat: @"%@ %@ )",
			[finalTextual length] ? @" OR (" : @"(",
			textual];
	}
		
	NSLog(@"TextualPredicate: %@", finalTextual);
	
	NSPredicate *predicate = nil;
	
	@try {
		predicate = [NSPredicate predicateWithFormat: finalTextual];
    } 
	@catch( NSException *exception )  {
        lpkwarningf("filtering", "could not parse lpPredicate '%@' (%@)", finalTextual, exception);

		NSLog(@"exc: n: %@ r: %@ u: %@", [exception name], [exception reason], [exception userInfo]);

		[self setErrorPtr: outError withCode: LOGPOINT_RETURN_BAD_FILTER userInfo: 
			[NSDictionary dictionaryWithObject: [exception reason] ?: NSLocalizedString(@"no reason given by NSPredicate parser", @"") forKey: NSLocalizedDescriptionKey]];		
	}

    return predicate;
}

#include "tracer.h"
+ (NSArray *) sharedLogPoints
{
	if( _sharedLogPoints == nil ) {
			_sharedLogPoints = [[NSMutableArray alloc] init]; // leak it

		lp_return_t err = logPointApply( NULL /*filter*/, NULL /*filterInfo*/, logPointCollector /*action*/, self /*actionInfo*/, LOGPOINT_OPTION_NONE);

		if( err != LOGPOINT_RETURN_OK ) {
			lpkwarningf("logpoints", "could not load logpoints: %s", logPointReturnString(err));
		}
    
	}
	
    return _sharedLogPoints;
}

- (NSArray *) sharedLogPoints
{
    return [[self class] sharedLogPoints];
}

- (id) initWithRawPointer: (void *) rawPointer
{
    if( nil == ( self = [super init] ) )
        return nil;

    raw = rawPointer;
    
    cachedKeys = nil;

    kindLength = 0;
    keysLength = 0;
    functionLength = 0;
    fileLength = 0;

    fileName = NULL;
    fileNameLength = 0;

    imageLength = 0;
    imageFileName = NULL;
    imageFileNameLength = 0;
    
    className = NULL;
    classNameLength = 0;
    
    selectorName = NULL;
    selectorNameLength = 0;
    
	const char *function = raw->function;
	
	// __-[ in block invocations
	const char *methodTypeLocation = ( '_' == function[0] && '_' == function[1] ) ? function + 2 : function;
		
    methodType = *methodTypeLocation;
    if( methodType == '+' || methodType == '-' ) {
        char *delim = strchr(raw->function, ' ');
        if( delim != NULL ) {
            className = methodTypeLocation + 2; // -[ 
            classNameLength = (size_t) delim - (size_t) className;

            char *closing = strchr(delim + 1, ']');
            
            if( closing != NULL ) {
                selectorName = delim + 1;
                selectorNameLength = (size_t) closing - (size_t) selectorName;
            } 
        }
    } else {
        methodType = 0;
    }

    return self;
}

- (void) dealloc
{
    if( cachedKeys ) {
        [cachedKeys release];
        cachedKeys = nil;
    }

    [super dealloc];
}

- (void *) rawPointer
{
    return raw;
}

- (NSString *) kind
{
    return SIMPLEWRAPPER(kind);
}

- (NSString *) commaSeparatedKeys
{
    return [[self keys] componentsJoinedByString: @","];
}

- (NSArray *) keys
{
    if( raw->keys == NULL )
        return NULL;

    if( cachedKeys )
        return cachedKeys;

	NSCharacterSet *whiteSet = [NSCharacterSet whitespaceCharacterSet];
    NSEnumerator *keyEnum = [[SIMPLEWRAPPER(keys) componentsSeparatedByString: @","] objectEnumerator];
	NSMutableArray *keys = [[NSMutableArray alloc] init];
	NSString *key;

    while( ( key = [keyEnum nextObject] ) ) {
      [keys addObject: [key stringByTrimmingCharactersInSet: whiteSet]];
    }
    
    return ( cachedKeys = keys );
}


- (NSString *) function
{
    return SIMPLEWRAPPER(function);
}

- (unichar) methodType
{
    return methodType;
}

- (NSString *) methodTypeAsString
{
	switch( methodType ) {
		case 0:   return nil;
		case '-': return @"-";
		case '+': return @"+";
	}
	
	return @"?";
}

- (NSString *) className
{
    return methodType == 0 ? nil : NSSTRINGWRAPPER(className, classNameLength);
}

- (NSString *) selectorName
{
    return methodType == 0 ? nil : NSSTRINGWRAPPER(selectorName, selectorNameLength);
}

- (NSString *) selectorNameWithTypePrefix
{
    return methodType == 0 ? nil : [[[self methodTypeAsString] stringByAppendingString: @" "] 
		stringByAppendingString: NSSTRINGWRAPPER(selectorName, selectorNameLength)];
}

- (NSString *) functionOrSelectorName
{
    return methodType == 0 ? [self function] : [self selectorName];
}

- (NSString *) functionOrSelectorNameWithTypePrefix
{
    return methodType == 0 ? [self function] : [self selectorNameWithTypePrefix];
}

- (NSString *) sourcePath
{
    return SIMPLEWRAPPER(file);
}

- (NSString *) sourceFileName
{
    if( raw->file == NULL )
        return nil;

    if( fileName == NULL ) {
        fileNameLength = [(NSString *)[[[self sourcePath] pathComponents] lastObject] length]; /* side effect: sets fileLength */
        fileName = raw->file + fileLength - fileNameLength;
    }

    return NSSTRINGWRAPPER(fileName, fileNameLength);
}

- (NSString *) binaryPath
{
    return SIMPLEWRAPPER(image);
}

- (NSString *) binaryFileName
{
    if( raw->image == NULL )
        return nil;
    
    if( imageFileName == 0 ) {
        imageFileNameLength = [(NSString *)[[[self binaryPath] pathComponents] lastObject] length]; /* side effect: sets imageLength */
        imageFileName = raw->image + imageLength - imageFileNameLength;
    }

    return NSSTRINGWRAPPER(imageFileName, imageFileNameLength);
}


- (NSInteger) line
{
    return (NSInteger) raw->line;
}

- (NSInteger) count
{
    return (NSInteger) raw->count;
}

- (void) setCount: (int) newCount
{
    raw->count = newCount;
}

- (void *) address
{
    return raw->address;
}

- (NSString *) addressAsString
{
    return [NSString stringWithFormat: @"%p", raw->address];
}


- (NSString *) formatInfo
{
    return SIMPLEWRAPPER(formatInfo);
}

- (NSString *) label
{
    return SIMPLEWRAPPER(label);
}

- (void) activate { 
	[self setActive: YES]; 
}

- (void) deactivate 
{
	if(NO == LOGPOINT_IS_HARD(*raw)) {
		[self setActive: NO]; 
	}
}

- (BOOL) isActive { return LOGPOINT_IS_ACTIVE(*raw); }
- (void) setActive: (BOOL) flag { LOGPOINT_SET_ACTIVE(*raw, flag); }

- (BOOL) isHard { return LOGPOINT_IS_HARD(*raw); }
- (void) setHard: (BOOL) flag { LOGPOINT_SET_HARD(*raw, flag); }

- (BOOL) isBroken { return LOGPOINT_IS_BROKEN(*raw); }
- (void) setBroken: (BOOL) flag { LOGPOINT_SET_BROKEN(*raw, flag); }

- (BOOL) isInDynamicCode { return LOGPOINT_IS_DYNAMIC_CODE(*raw); }
- (void) setInDynamicCode: (BOOL) flag { LOGPOINT_SET_DYNAMIC_CODE(*raw, flag); }

@end

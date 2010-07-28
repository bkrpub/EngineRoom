//
//  $Id: LogPoint.m 773 2009-02-24 00:45:22Z bkr $
//
//  Copyright (c) 2007 Bjoern Kriews
//

#import "LogPoint.h"

#import "logpoints_bk.h"

NSString *kLogPointUserDefaultsKey = @"logPointFilter";

#if 1
#undef lpwarning
#define lpwarning(keys, fmt, ...) /**/
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
        
    NSString *filter = [defaults valueForKey: kLogPointUserDefaultsKey];
        
	if( filter ) {	
		NSLog(@"LogPoint filter: %@", filter);
		
		NSError *error = nil;
		if( 0 > [self enableOnlyLogPointsMatchingFilterString: filter error: &error] ) {
			NSLog(@"could not compile LogPoint filter '%@' error: %@", filter, error);
			ret = NO;		
		}
	}

	// logPointDumpAll();

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
		lpwarning("filtering", "activated %u of %u filtered logpoints for '%@'", activated, filtered, [predicate predicateFormat]);
		return activated;
	} else {
		lpwarning("filtering", "no predicate given");
		return LOGPOINT_RETURN_BAD_FILTER;
	}
	
	
}

+ (NSPredicate *) predicateFromTextualRepresentation: (NSString *) textual error: (NSError **) outError
{
    if( textual == nil ) {
		[self setErrorPtr: outError withCode: LOGPOINT_RETURN_BAD_FILTER userInfo: nil];
        return nil;
	}
    
    if( ! [textual respondsToSelector: @selector(length)] || ! [textual respondsToSelector: @selector(rangeOfString:)] ) {
        lpwarning("filtering", "textual representation '%@' does not respond to length:, rangeOfString: - ignoring", textual);
		[self setErrorPtr: outError withCode: LOGPOINT_RETURN_BAD_FILTER userInfo: nil];
        return nil;
    }
 
	textual = [textual stringByTrimmingCharactersInSet: [NSCharacterSet whitespaceAndNewlineCharacterSet]];
	
	if( [textual length] > 1 ) {
		if( [textual hasPrefix: @","] ) {
			textual = [NSString stringWithFormat: @"keys CONTAINS '%@'", [textual substringFromIndex: 1]];
		}
	
		if( [textual hasPrefix: @"="] ) {
			textual = [NSString stringWithFormat: @"kind CONTAINS '%@'", [textual substringFromIndex: 1]];
		}
		
		if( [textual hasPrefix: @":"] ) {
			textual = [NSString stringWithFormat: @"selectorName BEGINSWITH '%@'", [textual substringFromIndex: 1]];
		}
	
		if( [textual hasPrefix: @"@"] ) {
			textual = [NSString stringWithFormat: @"className BEGINSWITH '%@'", [textual substringFromIndex: 1]];
		}

		if( [textual hasPrefix: @"?"] ) {
			textual = [NSString stringWithFormat: @"description CONTAINS '%@'", [textual substringFromIndex: 1]];
		}		
	}


    if( 0 == [textual length] ) {
        lpwarning("filtering", "interpreting empty string as false");
		textual = @"FALSEPREDICATE";
    }                    

    if( [textual isEqualToString: @"*"] ) {
        lpwarning("filtering", "interpreting * string as true");
		textual = @"TRUEPREDICATE";
    }                    	 
	
	 
    if( [textual rangeOfString: @"%"].location != NSNotFound ) {
        lpwarning("filtering", "textual representation '%@' contains a %% character - not supported - ignoring", textual);
		[self setErrorPtr: outError withCode: LOGPOINT_RETURN_BAD_FILTER userInfo: 
			[NSDictionary dictionaryWithObject: NSLocalizedString(@"% not supported in filter string - ignored", @"") forKey: NSLocalizedFailureReasonErrorKey]];
		return nil;
    } 
    
	NSLog(@"TextualPredicate: %@", textual);
	
	NSPredicate *predicate = nil;
	
	@try {
		predicate = [NSPredicate predicateWithFormat: textual];
    } 
	@catch( NSException *exception )  {
        lpwarning("filtering", "could not parse lpPredicate '%@' (%@)", textual, exception);

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
			lpwarning("logpoints", "could not load logpoints: %s", logPointReturnString(err));
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
    
    methodType = raw->function[0];
    if( methodType == '+' || methodType == '-' ) {
        char *delim = strchr(raw->function, ' ');
        if( delim != NULL ) {
            className = raw->function + 2; // +[
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
    return methodType == 0 ? nil : NSSTRINGWRAPPER(raw->function, 1);
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

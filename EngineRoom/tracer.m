//
//  $Id: tracer.m 755 2009-02-02 12:18:17Z bkr $
//

#include "tracer.c"

NSString *kTracerAddress       = @"kTracerSearchAddress";
NSString *kTracerSymbolOffset  = @"kTracerSymbolOffset";
NSString *kTracerSymbolAddress = @"kTracerSymbolAddress";
NSString *kTracerSymbolName    = @"kTracerSymbolName";
NSString *kTracerClassName     = @"kTracerClassName";
NSString *kTracerSelectorName  = @"kTracerSelectorName";
NSString *kTracerIsClassMethod = @"kTracerIsClassMethod";
NSString *kTracerImagePath     = @"kTracerImagePath";
NSString *kTracerImageName     = @"kTracerImageName";

#if 0
#import <ExceptionHandling/NSExceptionHandler.h>

/* unused because it does not seem reliable on 10.4 */
int backtrace_via_NSException(void **pcs, int size)
{
	NSExceptionHandler *ehandler = [NSExceptionHandler defaultExceptionHandler];
	unsigned oldMask = [ehandler exceptionHandlingMask];

	// this enables the NSStackTraceKey - found by experimentation - but does not work on 10.4 :-( 
	[ehandler setExceptionHandlingMask: oldMask | NSLogOtherExceptionMask];

	NSArray *trace = nil;

	@try { @throw [NSException exceptionWithName:@"TRACER_TRACE_EXCEPTION" reason:@"42" userInfo:nil]; } 
	@catch (id theException) {
		trace = [[[theException userInfo] valueForKey: NSStackTraceKey] componentsSeparatedByString: @"  "];
	} 

	[ehandler setExceptionHandlingMask: oldMask | NSLogOtherExceptionMask];

	NSLog(@"trace: %@", trace);

	int traceLen = [trace count];
	
	if( traceLen > 3 ) 
		traceLen -= 3;
	else 
		traceLen = 0;
	

	int i;
	for( i = 0 ; i < traceLen && i < size ; ++i ) {
		unsigned long long pc = strtoull([[trace objectAtIndex: i] UTF8String], NULL, 16);
		pcs[i] = (void*) (intptr_t) pc;
	}

	return i;
}
#endif

void UTIL_NO_INSTRUMENT
tracerRuntimeScannerInfoInit(TRACER_RUNTIME_SCANNER_INFO *info)
{
  memset(info, 0, sizeof(*info));
}

#if MAC_OS_X_VERSION_MIN_REQUIRED < 1050
Method *class_copyMethodList_emulation(Class cls, unsigned int *outCount) 
{
	void *iterator;
    struct objc_method_list *methodList;
	int methodCount = 0;
	int methodIdx;
 
	if( NULL != outCount ) 
		*outCount = 0;
 
	if( Nil == cls )
		return NULL;
 
	iterator = NULL;
    while( NULL != ( methodList = class_nextMethodList( cls, &iterator  ) ) )
		methodCount += methodList->method_count;
		
	if( 0 == methodCount )
		return NULL;
	
	Method *returnList = malloc( sizeof(Method) * methodCount+1 );
	
	if( nil == returnList ) 
		return NULL;
	
	int returnCount = 0;

	iterator = NULL;
    while( returnCount < methodCount && NULL != ( methodList = class_nextMethodList( cls, &iterator  ) ) ) {
		for( methodIdx = 0 ; methodIdx < methodList->method_count ; ++methodIdx ) {
			returnList[returnCount++] = &methodList->method_list[methodIdx];
		}
	}

    returnList[returnCount] = NULL;

    if( NULL != outCount ) 
      *outCount = returnCount;

    return returnList;
}
#endif
/* MAC_OS_X_VERSION_MIN_REQUIRED < 1050 */

void UTIL_NO_INSTRUMENT 
tracerScanMethodList(Class aClass, TRACER_RUNTIME_SCANNER_INFO *info)
{
	unsigned int methodCount;
	Method *theMethods = COMPAT_CLASS_COPYMETHODLIST( aClass, &methodCount );
	
	NSMutableString *methodNamePrefix = nil;
	BOOL isMetaClass = NO;
	
	info->methodCount += methodCount;
	
	unsigned int methodIdx;
	for( methodIdx = 0 ; methodIdx < methodCount ; ++methodIdx ) {
		Method aMethod = theMethods[ methodIdx ];
		uint64_t imp = UTIL_PTR_AS_ULL( COMPAT_METHOD_GETIMPLEMENTATION( aMethod ) );
		
		if( info->searchAddress >= imp ) {
		  uint64_t impOffset = info->searchAddress - imp;
		  		  
		  tracerDebugSymHeavy("search: %08llx ioff: %08llx off: %08llx [%s %s]", info->searchAddress, (unsigned long long) info->offset, (unsigned long long) impOffset, COMPAT_CLASS_GETNAME( aClass ), sel_getName( COMPAT_METHOD_GETNAME( aMethod) ) );

		  if( impOffset < info->offset ) {
		    info->nearestSymbolAddress = imp; 
		    info->nearestClass = aClass;
		    info->nearestSel = method_getName( aMethod );
		    info->offset = impOffset;		    
		  }
		}

		if( info->currentMethodArray || info->methodArray ) {
			if ( nil == methodNamePrefix ) {
				isMetaClass = COMPAT_CLASS_ISMETACLASS( aClass );
				methodNamePrefix = [NSMutableString stringWithString: isMetaClass ? @"+[" : @"-["];
				
				[methodNamePrefix appendString: info->currentClassName];
				[methodNamePrefix appendString: @" "];
			}
			
			NSString *selectorName = NSStringFromSelector( COMPAT_METHOD_GETNAME( aMethod ) );
			NSString *fullName = [[methodNamePrefix stringByAppendingString: selectorName] stringByAppendingString: @"]"];
			
			NSNumber *impNumber = [NSNumber numberWithUnsignedLongLong: (unsigned long long) imp];
			NSNumber *isClassMethod = [NSNumber numberWithBool: isMetaClass ? YES : NO];
				
			NSDictionary *methodDescription = [NSDictionary dictionaryWithObjectsAndKeys:
											   impNumber, @"symbolAddress",
											   info->currentClassName, @"className",
											   selectorName, @"selectorName",
											   fullName, @"symbolName",
											   isClassMethod, @"isClassMethod",
											   nil];
			
			if( info->currentMethodArray ) 
				[info->currentMethodArray addObject: methodDescription];
				
			if( info->methodArray ) 
				[info->methodArray addObject: methodDescription];
		}

	}

	free(theMethods);
}

BOOL UTIL_NO_INSTRUMENT
tracerScanClassList(TRACER_RUNTIME_SCANNER_INFO *info)
{
  info->classCount = 0;
  info->methodCount = 0;
  info->currentMethodArray = nil;

  unsigned int newClassCount = objc_getClassList(NULL, 0);

    Class *theClasses = NULL;
    while (info->classCount < newClassCount) {
        info->classCount = newClassCount;
        theClasses = realloc(theClasses, sizeof(Class) * info->classCount);
        newClassCount = objc_getClassList(theClasses, info->classCount);
    }

    if( NULL == theClasses )
      return NO;

	unsigned int classIdx;
	for(classIdx = 0 ; classIdx < info->classCount ; ++classIdx ) {
		
		Class aClass = theClasses[ classIdx ];

		if( nil == aClass )
			continue;

		info->currentClassName = NSStringFromClass( aClass );

// for testing
//		if(! [info->currentClassName hasPrefix: @"Little"] && ![info->currentClassName hasPrefix: @"NSButton"] ) 
//			continue;
			
		if( info->classArray ) {
			[info->classArray addObject: info->currentClassName];
		}
			
		if( info->classArray ) {
			info->currentMethodArray = [NSMutableArray array];
			[info->classDictionary setObject: info->currentMethodArray forKey: info->currentClassName];
		}
		
		Class aMetaClass = objc_getMetaClass( COMPAT_CLASS_GETNAME( aClass ) );
		
		if( nil != aMetaClass ) 
			tracerScanMethodList(aMetaClass, info);

		tracerScanMethodList(aClass, info);
	}
	
	free(theClasses);    

#if 0
	// sortUsingKeyPath is from a category
	if( info->methodArray ) {
		[info->methodArray sortUsingKeyPath: @"symbolAddress" ascending: YES];
		info->sortedIMPs = [info->methodArray valueForKey: @"symbolAddress"];

	}
#endif

	return YES;
}


NSDictionary * UTIL_NO_INSTRUMENT
tracerFrameInfoForAddress(uint64_t theAddress, TRACER_RUNTIME_SCANNER_INFO *info)
{
	info->imagePath = nil;
	info->nearestSymbol = nil;
	info->nearestSymbolAddress = 0;
	info->nearestClass = Nil;
	info->nearestSel = NULL;
	info->offset = 0;

	info->searchAddress = theAddress;
	
	if( NULL != info->symbolStore ) {
	  TRACER_SYMBOL *functionSymbol = NULL;

	  if( TRACER_SUCCESS == tracerSymbolStoreLookupByAddress(info->symbolStore, info->searchAddress, &functionSymbol, &info->offset) ) {
	    info->nearestSymbol = [NSString stringWithUTF8String: tracerSymbolStoreNameOfSymbol(info->symbolStore, functionSymbol)];
	    info->imagePath = [NSString stringWithUTF8String: tracerSymbolStoreImagePathOfSymbol(info->symbolStore, functionSymbol)];
	    info->nearestSymbolAddress = functionSymbol->value;
	  }
	}
  
	// scans all methods, updating fields in the info structure if something nearer is found

	tracerScanClassList(info);

	NSMutableDictionary *frame = [[NSMutableDictionary alloc] initWithCapacity: 10];

	if( info->nearestClass ) {
	  
	  BOOL isClassMethod = COMPAT_CLASS_ISMETACLASS( info->nearestClass );
	  NSString *className = [NSString stringWithUTF8String: COMPAT_CLASS_GETNAME( info->nearestClass )];
	  NSString *selectorName = [NSString stringWithUTF8String: sel_getName( info->nearestSel )];

	  info->nearestSymbol = [NSString stringWithFormat: @"%c[%@ %@]", isClassMethod ? '+' : '-', className, selectorName];

	  [frame setValue: [NSNumber numberWithBool: isClassMethod] forKey: kTracerIsClassMethod];
	  [frame setValue: className forKey: kTracerClassName];
	  [frame setValue: selectorName forKey: kTracerSelectorName];
	}

	[frame setValue: [NSNumber numberWithUnsignedLongLong: (unsigned long long) info->searchAddress] forKey: kTracerAddress];
	[frame setValue: [NSNumber numberWithUnsignedLongLong: (unsigned long long) info->offset] forKey: kTracerSymbolOffset];
	[frame setValue: [NSNumber numberWithUnsignedLongLong: (unsigned long long) info->nearestSymbolAddress] forKey: kTracerSymbolAddress];
	[frame setValue: info->nearestSymbol forKey: kTracerSymbolName];

	[frame setValue: info->imagePath forKey: kTracerImagePath];
	[frame setValue: [info->imagePath lastPathComponent] forKey: kTracerImageName];

	tracerDebugSym("addr: 0x%llx image: %s sym: %s (0x%llx) + %lld\n",
	      (unsigned long long)info->searchAddress, [info->imagePath UTF8String], [info->nearestSymbol UTF8String], (unsigned long long)info->nearestSymbolAddress, (unsigned long long) info->offset);	      
	

	NSDictionary *ret = [[frame mutableCopy] autorelease];
	[frame release];

	tracerDebugSym("frameInfo: %s", [[ret description] UTF8String]);

	return ret;
}

NSArray * UTIL_NO_INSTRUMENT
_tracerBacktraceAsArrayOfDictionaries(int skipFrames, void **pcs, int frames)
{
	TRACER_RUNTIME_SCANNER_INFO info;
	tracerRuntimeScannerInfoInit(&info);

	info.symbolStore = tracerSymbolStoreForLookupByAddress();

	NSMutableArray *trace = [NSMutableArray array];

	int i;
	for (i = skipFrames ; i < frames ; ++i) { 
	  if( pcs[i] > (void*) 0x8 ) /* there is a bug where argc shows up as a first frame if it is in the range 1..3 (OS X 10.5.2) */
	    [trace addObject: tracerFrameInfoForAddress( UTIL_PTR_AS_ULL( pcs[i] ), &info)];
	}

	tracerSymbolStoreRelease( info.symbolStore );

	return trace;
}

NSArray * UTIL_NO_INSTRUMENT
_tracerBacktraceAsArrayOfStrings(NSArray *trace)
{
  NSInteger frames = [trace count];
  
  NSMutableArray *strings = [NSMutableArray arrayWithCapacity: frames];
  
  int i;
  for( i = 0 ; i < frames ; ++i ) {
    NSDictionary *frameInfo = [trace objectAtIndex: i];
    
    [strings addObject: 
#ifdef __LP64__		 
	       [NSString stringWithFormat: @"%-3d %-35.35s 0x%016llx %@ + %lld", // format like backtrace_symbols()
#else
			 [NSString stringWithFormat: @"%-3d %-35.35s 0x%08llx %@ + %lld",
#endif
				   i,
				   [[frameInfo valueForKey: kTracerImageName] UTF8String],
				   [[frameInfo valueForKey: kTracerAddress] unsignedLongLongValue],
				   [frameInfo valueForKey: kTracerSymbolName],
				   [[frameInfo valueForKey: kTracerSymbolOffset] unsignedLongLongValue]
			  ]];
	     }
      
      return strings;
  }


#ifdef TRACER_TEST

@interface TracerTestObject : NSObject
- (void) tracerTestMethod: (id) someArg;
+ (void) dumpBacktrace;
@end

@implementation TracerTestObject

- (void) tracerTestMethod: (id) someArg
{
  [[self class] dumpBacktrace];
}

+ (void) dumpBacktrace
{
  // for comparing 
  // tracerDump();

  tracerDumpBacktrace();
}
@end

void tracerObjCDummy(TracerTestObject *t)
{
  fprintf(stderr, "Direct\n");

  [t tracerTestMethod: @"TestArg"];

  fprintf(stderr, "Through NSArray\n");

  NSArray *a = [NSArray arrayWithObject: t];

  [a makeObjectsPerformSelector: @selector(tracerTestMethod:) withObject: @"TestArg2"];
}

int tracerObjCTest(int argc, const char **argv)
{
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

  tracerBeginInstrumentation();

  TracerTestObject *test = [[TracerTestObject alloc] init];
  
  // IMP imp = [NSArray instanceMethodForSelector: @selector(makeObjectsPerformSelector:withObject:)];
  // fprintf(stderr, "imp: %p\n", imp);
  
  tracerObjCDummy(test);
  
  [test release];

  tracerEndInstrumentation();
    
  [pool release];

  return 0;
}

int main(int argc, const char **argv)
{
  return tracerObjCTest(argc, argv);
}

#endif
/* TRACER_TEST */

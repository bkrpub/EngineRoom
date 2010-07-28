#include <stdio.h>
#include <stdlib.h>

#include "logpoints_bk.h"

#import <Foundation/Foundation.h>

@interface LogPointTest : NSObject
- (void) someMethod: (id) someArg;
@end

@implementation LogPointTest

- (void) someMethod: (id) someArg
{
	lpdebug1("calculation", someArg);

	if( lpdebugswitch("objcbomb", NULL) ) {
		lperror("objcbomb", "the switch is on but the bulb is done");
		LPAssert( 1 == 0, @"bulb bad" );
	}
}

@end

void foo(int bar)
{
  lpcdebug("calculation", "%d", bar);
  lpcInt("calculation", bar);  

  if( lpcswitch("cbomb", NULL) ) {
    lpcerror("cbomb", "the switch is on but the bulb is done");
    LPCAssert( 1 == 0, @"bulb bad" );
  }

  usleep(15000);
}

int main(int argc, char **argv)
{
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

  logPointEnableSimple(getenv("LP_FILTER"));

  dbugC(argc);
  dbugC(&argc);
  dbugC(argv);
  dbugC(argv[0]);
  dbugC(*argv[0]);
  dbugC(argv[1]);
  dbugC(getenv("LP_FILTER"));

  if( argv[1] && 0 == strcmp( argv[1], "-d" ) ) {
    logPointDumpAll();
    exit(0);
  }
  
  lpcInt("setup,parameters", argc);


  dbug_oC(@"constantnsstring");
  dbug_oC(CFSTR("constantcfstring"));

  NSMutableString *nsstr = nil;
  dbug_oC(nsstr);
  nsstr = [[NSMutableString alloc] init];
  dbug_oC(nsstr);
  [nsstr appendString: @"nonempty"];
  dbug_oC(nsstr);

  CFStringRef cfstr = CFStringCreateWithFormat(kCFAllocatorDefault, NULL, CFSTR("cf fmt"));
  CFArrayRef cfarr = CFStringCreateArrayBySeparatingStrings(kCFAllocatorDefault, cfstr, CFSTR(" "));
  dbug_cfC(cfstr);
  dbug_cfC(cfarr);

  foo(23);
  foo(42);

  lpcerror("shutdown", "not yet implemented");
  
  LogPointTest *t = [[LogPointTest alloc] init];
  [t someMethod: @"TestArg"];
  [t release];
	
  [pool release];

  return 0;
}


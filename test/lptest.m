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


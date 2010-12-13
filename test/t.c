

#import <Foundation/Foundation.h>

#import <EngineRoom/logpoints_default.h>

@interface Foo : NSObject
+ (id) barArgc: (int) argc argv: (char **) argv;
@end

@implementation Foo

+ (id) barArgc: (int) argc argv: (char **) argv
{
  NSRect rect = { { 1, 2 }, { 3, 4 } };
  NSRange range = { 23, 42 };

  struct timeval tv;

  gettimeofday(&tv, NULL);

  lpdebug(rect, tv);
  
  NSNumber *argcNumber = lpdebug_expr( [NSNumber numberWithInteger: argc] );
 
  return_lpwarning( argcNumber );
}

@end


int main(int argc, char **argv) {

  logPointEnableSimple("");

  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

  lpcdebug(argc, argv, argv[0], *argv[0]);

  LOGPOINT *lp;
  if( ( lp = lpcassertf(argv[1], "need an argument") ) ) {
    lpcdebug(lp);
  }

  [Foo barArgc: argc argv: argv];

  NSLog(@"we are %@", @"original");

#import "logpoints_nslog.h"

  NSLog(@"we are %@", @"substituted");
  
  [pool drain];

  return 0;
}

#include <stdio.h>
#import <Foundation/Foundation.h>

@interface ArgTest : NSObject

+ (BOOL) noCrash;
+ (void) crash;

@end

@implementation ArgTest

+ (BOOL) noCrash
{
  void *args = __builtin_apply_args();
  printf("args: %p\n", args);
  return args ? YES : NO;
}

+ (void) crash
{
  void *args = __builtin_apply_args();
  printf("args: %p\n", args);
}

@end

int main(int argc, char **argv)
{
  [ArgTest noCrash];
  [ArgTest crash];
  return 0;
}


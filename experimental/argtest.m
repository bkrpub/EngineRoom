#include <stdio.h>
#import <Foundation/Foundation.h>

#define LP_ARGS __builtin_apply_args(), __builtin_frame_address(0)
#define LP_FUNC __PRETTY_FUNCTION__


void *retself(void *self, void *_cmd)
{
  /* printf("retself: %p %p\n", self, _cmd); */
  return self;
}

void *getself(void *args)
{
  __builtin_return( __builtin_apply((void (*)()) retself, args, 3 * sizeof(void*) ) );
  
  //void **argp = *(void ***) args;
  //return argp[0];

  //return NULL;
}


void logger(const char *tag, id realself, id *selfaddr, void *args, void *frame)
{
  void **f = (void**) frame; 
  void **a = (void**) args;
  //  fprintf(stderr, "%-20.20s: self: %p &self: %p frame: %p = %p %p %p %p\n", tag, realself, selfaddr, f, f[0], f[1], f[2], f[3]); 
  fprintf(stderr, "%-20.20s: self: %p &self: %p args:  %p = %p %p %p %p\n", tag, realself, selfaddr, a, a[0], a[1], a[2], a[3]); 

#if 0
  id fakeself = (*tag =='+' || *tag == '-') ? getself(args) : NULL;
  
  printf("%-40.40s: self: %p getself: %p\n", tag, realself, fakeself);
  if( realself != fakeself ) { fprintf(stderr, "FAIL !!!!\n"); /*exit(1);*/ }  
#endif
}

void funcVoid(id self, char *_cmd)
{
  logger(LP_FUNC, self, &self, LP_ARGS);
}

void *funcId(id self, char *_cmd)
{
  logger(LP_FUNC, self, &self, LP_ARGS);
  return self;
}

void cFuncVoid(void)
{
  logger(LP_FUNC, NULL, NULL, LP_ARGS);
}

int cFuncArgs(int a, int b)
{
  logger(LP_FUNC, NULL, NULL, LP_ARGS);
  return a+b;
}



@interface ArgTest : NSObject

+ (void) classVoid;
+ (id) classId;
- (void) instanceVoid;
- (int) heightFromPoint: (NSPoint) p width: (float) width height: (int) height;
- (float) originFromPoint: (NSPoint) p width: (float) width height: (int) height;
- (NSRect) rectFromPoint: (NSPoint) p width: (float) width height: (int) height;

@end

@implementation ArgTest

+ (void) classVoid
{
  logger(LP_FUNC, self, &self, LP_ARGS);
}

+ (id) classId
{
  logger(LP_FUNC, self, &self, LP_ARGS);
  return [[self alloc] init];
}

- (void) instanceVoid
{
  logger(LP_FUNC, self, &self, LP_ARGS);
}

- (int) heightFromPoint: (NSPoint) p width: (float) width height: (int) height
{
  logger(LP_FUNC, self, &self, LP_ARGS);
  return height;
}


- (float) originFromPoint: (NSPoint) p width: (float) width height: (int) height
{
  logger(LP_FUNC, self, &self, LP_ARGS);
  return p.x;
}

- (NSRect) rectFromPoint: (NSPoint) p width: (float) width height: (int) height
{
  logger(LP_FUNC, self, &self, LP_ARGS);
  return NSMakeRect(p.x,p.y,width,height);
}

@end

int main(int argc, char **argv)
{
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

  void *ret;

  /*
  funcVoid((void*)0x23, (void*)0x42);
  ret = funcId((void*)0x23, (void*)0x42);

  printf("funcId: %p\n", ret);
  */

  cFuncVoid();


  int sum = cFuncArgs(23,42);
  
  printf("cFuncArgs: %d\n", sum);

  [ArgTest classVoid];
  ArgTest *a = [ArgTest classId];

  printf("classId: %p\n", a);

  [a instanceVoid];


  int h = [a heightFromPoint: NSMakePoint(1.2,3.4) width: 5.6 height: 7.8];

  printf("h: %d\n", h);


  float o = [a originFromPoint: NSMakePoint(1.2,3.4) width: 5.6 height: 7.8];

  printf("o: %f\n", o);

  NSRect r = [a rectFromPoint: NSMakePoint(1.2,3.4) width: 5.6 height: 7.8];

  printf("r: %s\n", [NSStringFromRect(r) UTF8String]);

  [pool release];

  return 0;
}


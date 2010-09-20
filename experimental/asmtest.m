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
#import <Foundation/Foundation.h>
#import <objc/runtime.h>
#import <objc/message.h>

#import "../tracer.h"

#define LP_ARGS getfp(), getsp(), tracerBacktraceAsString(0,NULL)
#define LP_FUNC __PRETTY_FUNCTION__

#ifdef __LP64__
#define getfp() ({ void * volatile * volatile __rbp; __asm__ volatile ("movq %%rbp, %0" : "=r" (__rbp) ); (__rbp); })
#define getsp() ({ void * volatile * volatile __rsp; __asm__ volatile ("movq %%rsp, %0" : "=r" (__rsp) ); (__rsp); })
#else
#define getfp() ({ void * volatile * volatile __ebp; __asm__ volatile ("movl %%ebp, %0" : "=r" (__ebp) ); (__ebp); })
#define getsp() ({ void * volatile * volatile __esp; __asm__ volatile ("movl %%esp, %0" : "=r" (__esp) ); (__esp); })
#endif

void logger(const char *function, id realself, id *selfaddr, void * volatile * volatile fp, void * volatile * volatile sp, NSString *trace)
{
  id theSelf = 0;
  NSUInteger retLen;

  if( ( '+' == *function || '-' == *function ) && '[' == function[1] && 0 != function[2] ) {
    int len = strlen(function);
    char *buf = alloca(len+1);
    strcpy(buf, function);
    char *className = buf + 2; 
    char *selName = strchr(className, ' ');
    if( selName ) {
      *selName = 0; /* terminate class name */
      ++selName; /* skip space */
      buf[len-1] = 0; /* terminate sel name */

      //fprintf(stderr, "looking up %c %s %s\n", *buf, className, selName);

      Class theClass = objc_getClass(className);

      // fprintf(stderr, "class is %p\n", theClass);

      if( theClass ) {
      
	SEL theSel = sel_getUid(selName);

	//fprintf(stderr, "SEL is %p\n", theSel);

	if( theSel ) {

	  NSMethodSignature *theSig = ('+' == *buf) ? [theClass methodSignatureForSelector: theSel] : [theClass instanceMethodSignatureForSelector: theSel];
	  Method theMethod = ('+' == *buf) ? class_getClassMethod(theClass, theSel) : class_getInstanceMethod(theClass, theSel);
	  
	  //NSLog(@"theSig: %p", theSig);

	  if( theSig ) {
	    
	    retLen = [theSig methodReturnLength];
	    const char *retType = [theSig methodReturnType];
	    int args = [theSig numberOfArguments];
	    int frameLength = [theSig frameLength];
	    int i;
	    
	    fprintf(stderr, "retLen(%s): %d frame: %d", retType, (int) retLen, (int)frameLength);
	    for(i=0;i<args;++i)
	      fprintf(stderr, " arg%d: %s", i, [theSig getArgumentTypeAtIndex: i]);
	    fprintf(stderr, "\n");

	    if( retLen > 2 * sizeof(void*) ) {
#ifdef __LP64__
	      theSelf = *(fp-3);
#else
	      theSelf = *(fp+3);
#endif
	    } else {
#ifdef __LP64__
	      theSelf = *(fp-3);
#else
	      theSelf = *(fp+2);
#endif
	    }

	  }

	}
	
      }
    }
    
  }

  fprintf(stderr, "%s %-20.20s: rl: %d fp: %p sp: %p self: %p &self: %p theSelf: %p dfp: %ld dsp: %ld\n", 
	  realself == theSelf ? " OK " : "FAIL", function, (int) retLen, fp, sp, realself, selfaddr, theSelf,
	  (long) fp - (long) selfaddr,  
	  (long) sp - (long) selfaddr);

  NSLog(@"trace:\n%@\n---", trace);
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
- (double) doriginFromPoint: (NSPoint) p width: (float) width height: (int) height;
- (NSRect) rectFromPoint: (NSPoint) p width: (float) width height: (int) height;
- (NSRect) rectFromRect: (NSRect) r, ...;
- (int) add: (int) one, ...;
- (int) sub: (int) one;
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


- (double) doriginFromPoint: (NSPoint) p width: (float) width height: (int) height
{
  logger(LP_FUNC, self, &self, LP_ARGS);
  return p.x;
}


- (NSRect) rectFromPoint: (NSPoint) p width: (float) width height: (int) height
{
  NSLog(@"foo");
  logger(LP_FUNC, self, &self, LP_ARGS);
  return NSMakeRect(p.x,p.y,width,height);
}

- (NSRect) rectFromRect: (NSRect) r, ...
{
  logger(LP_FUNC, self, &self, LP_ARGS);
  va_list ap;
  logger(LP_FUNC, self, &self, LP_ARGS);
  va_start(ap, r);
  logger(LP_FUNC, self, &self, LP_ARGS);
  va_end(ap);
  logger(LP_FUNC, self, &self, LP_ARGS);
  return r;
}

- (int) add: (int) one, ...
{
  int two = 2* one;
  va_list ap;
  va_start(ap, one);
  logger(LP_FUNC, self, &self, LP_ARGS);
  va_end(ap);
  int three = printf("foo");
  char *tmp = alloca(256);
  logger(LP_FUNC, self, &self, LP_ARGS);
  return three;
}

- (int) sub: (int) one
{
  int two = 2* one;
  va_list ap;
  logger(LP_FUNC, self, &self, LP_ARGS);
  int three = printf("foo");
  char *tmp = alloca(256);
  logger(LP_FUNC, self, &self, LP_ARGS);
  return three;
}


void dummy(char *s, void *p) {}

- (void) simpleSelf { dummy("SELF", self); }
- (void) simpleCmd { dummy("_CMD", _cmd); }
- (NSRect) rectSelf { dummy("SELF", self); return NSZeroRect; }
- (NSRect) rectCmd { dummy("_CMD", _cmd); return NSZeroRect; }




@end

struct str64 {
  unsigned long long a,b,c,d;
};

void stackTest()
{

  fprintf(stderr, "sp: %p\n", getsp());
  char a[32];
  a[0]='A';
  fprintf(stderr, "sp: %p a: %p\n", getsp(), a);
  char *b = alloca(32);
  *b='B';
  fprintf(stderr, "sp: %p b: %p\n", getsp(), b);
  char *c = ({ char *_c = alloca(32); _c; });
  *c = 'C';
  fprintf(stderr, "sp: %p c: %p\n", getsp(), c);

  char *d = ({ char _d[32]; _d; });
  *d = 'D';
  fprintf(stderr, "sp: %p e: %p\n", getsp(), d);

  char *e = ({ char *_e = alloca(32); _e; });
  *e = 'E';
  fprintf(stderr, "sp: %p d: %p\n", getsp(), e);  

  char *f = ({ char _f[32]; _f; });
  *f = 'F';

  fprintf(stderr, "sp: %p f: %p\n", getsp(), f);

  fprintf(stderr, "a: %c b: %c c: %c d: %c e: %c f: %c\n",*a,*b,*c,*d,*e,*f);
}

int main(int argc, char **argv)
{
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

  stackTest();
  return 0;

  void *ret;

  /*
  funcVoid((void*)0x23, (void*)0x42);
  ret = funcId((void*)0x23, (void*)0x42);

  printf("funcId: %p\n", ret);
  */

  //cFuncVoid();


  //int sum = cFuncArgs(23,42);
  
  //printf("cFuncArgs: %d\n", sum);

  [ArgTest classVoid];
  ArgTest *a = [ArgTest classId];

  printf("classId: %p\n", a);

  [a instanceVoid];


  int h = [a heightFromPoint: NSMakePoint(1.2,3.4) width: 5.6 height: 7.8];

  printf("h: %d\n", h);


  float o = [a originFromPoint: NSMakePoint(1.2,3.4) width: 5.6 height: 7.8];
  double d = [a doriginFromPoint: NSMakePoint(1.2,3.4) width: 5.6 height: 7.8];

  printf("o: %f d: %lf\n", o,d);

  NSRect r = [a rectFromPoint: NSMakePoint(1.2,3.4) width: 5.6 height: 7.8];

  r = [a rectFromRect: r, 23,43];

  struct str64 st;

  [a add: 1];
  [a sub: 1];

  [a add: 1, 17, st];


  printf("r: %s\n", [NSStringFromRect(r) UTF8String]);

  [pool release];

  return 0;
}


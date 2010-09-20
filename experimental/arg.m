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

#define LP_ARGS __builtin_apply_args()
#define LP_FUNC __PRETTY_FUNCTION__


void *retself(void *self, void *_cmd)
{
  return self;
}

void *getself(void *args)
{
  __builtin_return( __builtin_apply((void (*)()) retself, args, 2 * sizeof(void*) ) );
}


void logger(const char *tag, id realself, void *args)
{
  id fakeself = (*tag =='+' || *tag == '-') ? getself(args) : NULL;
  
  printf("%-40.40s: self: %p getself: %p\n", tag, realself, fakeself);
  if( realself != fakeself ) { fprintf(stderr, "FAIL !!!!\n"); /*exit(1);*/ }  
}

void cFuncVoid(void)
{
  logger(LP_FUNC, NULL, LP_ARGS);
}

int cFuncArgs(int a, int b)
{
  logger(LP_FUNC, NULL, LP_ARGS);
  return a+b;
}

@interface ArgTest : NSObject

- (float) xFromPoint: (NSPoint) p;
- (NSRect) rectFromPoint: (NSPoint) p width: (float) width height: (int) height;
- (void) nop;
+ (void) classNop;

@end

@implementation ArgTest

- (float) xFromPoint: (NSPoint) p
{
  logger(LP_FUNC, self, LP_ARGS);
  return p.x;
}

- (NSRect) rectFromPoint: (NSPoint) p width: (float) width height: (int) height
{
  logger(LP_FUNC, self, LP_ARGS);
  return NSMakeRect(p.x,p.y,width,height);
}

- (void) nop
{
  logger(LP_FUNC, self, LP_ARGS);
}


+ (void) classNop
{
  logger(LP_FUNC, self, LP_ARGS);
}



@end

int main(int argc, char **argv)
{
  NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

  cFuncArgs(23,42);
  
  ArgTest *a = [[ArgTest alloc] init];

  float x = [a xFromPoint: NSMakePoint(1.2,3.4)];

  printf("x: %f\n", x);

  NSRect r = [a rectFromPoint: NSMakePoint(1.2,3.4) width: 5.6 height: 7.8];

  printf("r: %s\n", [NSStringFromRect(r) UTF8String]);

  [a nop];

  [ArgTest classNop]; /* had semi-reproducible crashes with -fomit-frame-pointer on x86_64 */

  [pool release];

  return 0;
}


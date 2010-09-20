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

void getoff(int *p1, int *p2)
{
  void *frame = __builtin_frame_address(0);
  void *vp1 = &p1;
  void *vp2 = &p2;

  printf("diff: %d, %d\n", vp1-frame, vp2-frame);

  *p1 = ( vp1 > frame ? (int)(vp1-frame) : -(int)(frame-vp1) ) / sizeof(void*);
  *p2 = ( vp2 > frame ? (int)(vp2-frame) : -(int)(frame-vp2) ) / sizeof(void*);

  printf("frame: %p &p1: %p &p2: %p sovp: %d p1: %d p2: %d\n", 
	 frame, vp1, vp2, sizeof(void*), *p1, *p2);


}

void func(void *a, char *b)
{
  int f1, f2;
  getoff(&f1, &f2);

  void **frame = __builtin_frame_address(0);

  printf("frame: %p &a: %p &b: %p a: %p b: %p frame[%d]: %p frame[%d]: %p\n", 
	 frame, &a, &b, a, b, f1, frame[f1], f2, frame[f2]);

}

struct objc_args { void *self_arg; void *cmd_arg; };

void *retself(void *self, void *_cmd)
{
  printf("retself: %p %p\n", self, _cmd);
  return self;
}

void *getself(void *args)
{
  __builtin_return( __builtin_apply((void (*)()) retself, args, 2 * sizeof(void*) ) );
}

void testself(void *self, char *_cmd)
{
  void *myself = getself( __builtin_apply_args() );

  printf("myself: %p\n", myself);
}

main()
{
  testself((void*)0x23, (void*)0x42);

}

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


#import <Foundation/Foundation.h>
#include <stdio.h>

@interface Foo : NSObject
+ (void) bar;
- (void) baz;
- (NSRect) rect;
- (NSRect) rect: (NSRect) r foo: (id) x;
- (unsigned long long) ull;
- (unsigned long long) ull: (NSRect) r foo: (id) x;
- (double) dbl;
- (double) dbl: (NSRect) r foo: (id) x;
@end

#define SHOW do{ id *f = (id*) __builtin_frame_address(0); fprintf(stderr, "%-20.20s: self: %p &self: %p frame: %p = %p %p %p %p\n", __PRETTY_FUNCTION__, self, &self, f, f[0], f[1], f[2], f[3]); }while(0)

@implementation Foo
+ (void) bar 
{
  SHOW;
}

- (void) baz
{
  SHOW;
}

- (NSRect) rect
{
  SHOW;
  return NSZeroRect;
}

- (NSRect) rect: (NSRect) r foo: (id) x
{
  SHOW;
  return NSMakeRect(r.origin.x+1,r.origin.y+1,r.size.width,r.size.height);
}

- (unsigned long long) ull
{
  SHOW;
  return (unsigned long long) 0ULL;
}

- (unsigned long long) ull: (NSRect) r foo: (id) x
{
  SHOW;
  return (unsigned long long) r.origin.x;
}

- (double) dbl
{
  SHOW;
  return (double) 0;
}

- (double) dbl: (NSRect) r foo: (id) x
{
  SHOW;
  return (double) r.origin.x;
}



@end


int main(int argc, const char **argv)
{
  //  int x = __builtin_choose_expression( self, 1, 0);
  // int myself __attribute__ ((alias ("self")));
  
  Foo *f = [[Foo alloc] init];
  
  NSRect r;
  unsigned long long ull;
  double d;
  
  [Foo bar];
  [f baz];
  r = [f rect];
  r = [f rect: NSZeroRect foo: @"blah"];
  ull = [f ull];
  ull = [f ull: NSZeroRect foo: @"blah"];
  d = [f dbl];
  d= [f dbl: NSZeroRect foo: @"blah"];

return 0;
}

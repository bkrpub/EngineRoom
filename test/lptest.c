#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logpoints_bk.h"

int foo(int bar)
{
  lpcInt("calculation", bar);  

  if( lpcswitch("fullmoon", "multiply result by 2" ) ) {
	bar *= 2;
  }

  lpcdebug("calculation", "result bar: %d", bar);

  dbug_return_int(bar);
}

int main(int argc, char **argv)
{
  // filter is a comma separated list of substrings to search 
  // the current simple filter searches only the keys given to the logpoints
  logPointEnableSimple(getenv("LP_FILTER")); 

  dbug(argc);
  dbug(&argc);
  dbug(argv);
  dbug(argv[0]);
  dbug(*argv[0]);
  dbug(argv[1]);
  dbug(getenv("LP_FILTER"));

  if( argv[1] && 0 == strcmp( argv[1], "-d" ) ) {
	logPointDumpAll();
	exit(0);
  }

  int x = 23;
  int y = 42;

  if( lpcdebugswitch("halfmoon", "increment x/y before use" ) ) {
	++x;
	++y;
  }

  lpcInt("setup,parameters", argc);

  printf("1. foo(%d) is %d\n", x, foo(x));
  printf("2. foo(%d) is %d\n", y, foo(y));

  lpcerror("shutdown", "this message is always on");

  return 0;
}


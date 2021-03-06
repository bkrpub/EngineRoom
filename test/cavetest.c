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

#include <sys/time.h>

#define cavemanFormatStructTimezone(tz, label)					\
  cavemanFormat("struct timezone: %s = GMT %+0.2d%02d (%d minutes west) DST: %d", label, \
		-((tz)->tz_minuteswest) / 60, (tz)->tz_minuteswest % 60, (tz)->tz_minuteswest, (tz)->tz_dsttime)

void *cavemanFormatStructTimeval(struct timeval *tv, const char *label); 

#define cavemanSupportedUserCType(value)		  \
  cavemanTypeIs_opt_const((value),  struct timeval ) || \
  cavemanTypeIs_opt_const((value),  struct timezone ) || \
  0

#define cavemanFormatUserCTypes(value, localvalue, label)	     \
  if( cavemanTypeIs_opt_const((value),  struct timeval ) )			\
    cavemanReturn = cavemanFormatStructTimeval( (struct timeval *) &(localvalue), (label) ); \
  if( cavemanTypeIs_opt_const((value),  struct timezone ) )			\
    cavemanReturn = cavemanFormatStructTimezone( (struct timezone *) &(localvalue), (label) ); \
  ;

#include "caveman.h"

void *cavemanFormatStructTimeval(struct timeval *tv, const char *label)
{
  struct timezone tz; 
  gettimeofday(NULL, &tz); 
  time_t t = (time_t) (tv)->tv_sec; 
  char buf[26];
  return (void *) cavemanFormat("struct timeval: %s = %llu.%06llu = %.24s %+0.2d%02d", 
		       label, (unsigned long long) t, (unsigned long long) tv->tv_usec, 
		       ctime_r(&t, buf), -tz.tz_minuteswest / 60, tz.tz_minuteswest % 60);
}


void arrays(char carray[], int iarray[])
{
 caveman(carray);
 caveman(iarray);
}

int main(int argc, const char *argv[]) 
{
  caveman(argc);
  caveman(&argc);
  caveman(argv);
  caveman(argv[0]);
  caveman(*argv[0]);
  caveman(argv[1]);

  const char * const cptr = "test";
  caveman(cptr);
  caveman(*cptr);

  const signed char * const scptr = (signed char *) "test";
  caveman(scptr);
  caveman(*scptr);

  const unsigned char * const ucptr = (unsigned char *) "test";
  caveman(ucptr);
  caveman(*ucptr);

  char carray[2];
  carray[0]='*';
  carray[1]=0;
  cavearray(carray);
  /* caveman(carray); */

  int iarray[] = {23,42};
  cavearray(iarray);
  /* caveman(iarray); */

  caveman("test"); 

  arrays(carray, iarray);

  /*  
  BOOL booly = NO;
  caveman(booly);
  */

  char aChar = -2;
  caveman(aChar);
  caveman(&aChar);

  unsigned char signedChar = -2;
  caveman(signedChar);
  caveman(&signedChar);

  unsigned char unsignedChar = 0xfe;
  caveman(unsignedChar);
  caveman(&unsignedChar);

  unsigned const short ushorty = 0x423;
  caveman(ushorty);
  caveman(&ushorty);

  unsigned const long ulongy = 0x423;
  caveman(ulongy);
  caveman(&ulongy);

  unsigned const long long ulonglongy = 0x423;
  caveman(ulonglongy);
  caveman(&ulonglongy);

  const float aFloat = 23.42;
  caveman(aFloat);
  caveman(&aFloat);

  const double aDouble = 23.42;
  caveman(aDouble);
  caveman(&aDouble);

  const long double aLongDouble = 23.42;
  caveman(aLongDouble);
  caveman(&aLongDouble);

  cavestr(argv[0]);
  cavestr(argv[1]);

  struct timeval tv;
  struct timezone tz;
  gettimeofday(&tv, &tz);
  caveman(tv.tv_sec);
  caveman(tv.tv_usec);
  caveman(tv);
  caveman(tz.tz_minuteswest);
  caveman(tz);

  enum { MinusOne = -1, One = 1, Two = 2 } anEnum = Two;
  caveman(anEnum);

#ifdef TESTBAD
  struct { int x; } bad;
  caveman(bad);
#endif

  return 0;
}

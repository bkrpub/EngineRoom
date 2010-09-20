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

// gcc -o str str.m -framework Foundation

#import <Foundation/Foundation.h>

int main(int argc, const char **argv)
{
  unichar characters[] = { 'o', 'e', ':', 0xf6, ' ', 'p', 'h', 'i', ':', 0x278 };

  CFStringRef str = CFStringCreateWithCharacters(kCFAllocatorDefault, characters, sizeof(characters) / sizeof(characters[0]));

  CFStringBuiltInEncodings encoding = argc>1 ? strtol(argv[1], NULL, 16) : kCFStringEncodingUTF8;
  UInt8 lossByte = argc>2 ? *argv[2] : 0;


  CFIndex strlen = CFStringGetLength(str);
  CFIndex buflen = CFStringGetMaximumSizeForEncoding( strlen, encoding ) + 1;
  CFIndex usedbuflen = 0;
  CFIndex converted = 0;

  NSLog(@"str: '%@' strlen=%d buflen=%d", str, (int)strlen, (int)buflen);

  UInt8 *buffer = malloc( buflen * sizeof(UInt8) );

  //CFStringCreateExternalRepresentation(CFAllocatorRef alloc, CFStringRef theString, CFStringEncoding encoding, UInt8 lossByte);

  converted = CFStringGetBytes(str, CFRangeMake(0, strlen), encoding, lossByte, false, buffer, buflen - 1, &usedbuflen);
  
  buffer[usedbuflen] = 0;
  
  NSLog(@"converted=%d usedbuflen=%d", (int)converted, (int) usedbuflen);
  
  printf("pf buffer: '%s'\n", buffer);
  NSLog(@"ns1 buffer: '%s'\n", buffer);
  NSLog(@"ns2 buffer: '%@'\n", [[NSString alloc] initWithUTF8String: buffer]);
  NSLog(@"ns3 buffer: '%@'\n", [[NSString alloc] initWithFormat: @"%s", buffer]);

  return 0;
}


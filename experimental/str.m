/* gcc -o str str.m -framework Foundation */

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


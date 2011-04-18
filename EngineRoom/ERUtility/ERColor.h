/*
Copyright (c) 2010, Bjoern Kriews
All rights reserved.

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

#import <EngineRoom/EngineRoom.h>

@interface ERColor : NSObject <NSCopying> {
	NSString *m_genericRGBAString;
	CGColorRef m_CGColor;
#if TARGET_OS_OSX
	NSColor *m_NSColor;
#endif
}

+ (ERColor *) colorWithGenericRGBAString: (NSString *) genericRGBAString;

+ (ERColor *) colorWithCGColor: (CGColorRef) cgColor;

#if TARGET_OS_OSX
+ (ERColor *) colorWithNSColor: (NSColor *) nsColor;
#endif

- (id) initWithGenericRGBAString: (NSString *) genericRGBAString;

- (id) initWithCGColor: (CGColorRef) cgColor;

#if TARGET_OS_OSX
- (id) initWithNSColor: (NSColor *) nsColor;
#endif

- (NSString *) genericRGBAString;
- (void) setGenericRGBAString: (NSString *) genericRGBAString;

- (CGColorRef) CGColor;
- (void) setCGColor: (CGColorRef) CGColor;

#if TARGET_OS_OSX
- (NSColor *) NSColor;
- (void) setNSColor: (NSColor *) nsColor;
#endif

@end

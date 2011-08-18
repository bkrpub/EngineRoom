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

#import <QuartzCore/QuartzCore.h>

#import "ERColor.h"
#import <EngineRoom/EngineRoom.h>
#import <EngineRoom/er_util.h>

#if TARGET_OS_OSX
NSString *GenericRGBAStringFromColor(NSColor *color)
{
	if( nil == color ) {
		return nil;
	}

	NSColor *genericRGBColor = [color colorUsingColorSpace: [NSColorSpace genericRGBColorSpace]];

	CGFloat comps[4] = {0,0,0,0};
	
	[genericRGBColor getComponents: comps];
	
	return [NSString stringWithFormat: @"#%02lx%02lx%02lx%02lx", (long)(0xff * comps[0]), (long)(0xff * comps[1]), (long)(0xff * comps[2]), (long)(0xff * comps[3])];
}
#endif

NSString *GenericRGBAStringFromCGColor(CGColorRef cgColor)
{
	if( NULL == cgColor ) {
		return nil;
	}

	NSCAssert( 4 == CGColorGetNumberOfComponents(cgColor),  @"colors with comp# != 4 not supported");

	const CGFloat *comps = CGColorGetComponents( cgColor );
	return [NSString stringWithFormat: @"#%02lx%02lx%02lx%02lx", (long)(0xff * comps[0]), (long)(0xff * comps[1]), (long)(0xff * comps[2]), (long)(0xff * comps[3])];
}

CGColorRef CreateCGColorFromGenericRGBAString(NSString *genericRGBAString)
{
	if( nil == genericRGBAString ) {
		return NULL;
	}

	long hexComps[] = {0,0,0,255};
	CGFloat comps[] = {0,0,0,1};
	
	NSCAssert( 4 == sscanf([genericRGBAString UTF8String], "#%02lx%02lx%02lx%02lx", &hexComps[0], &hexComps[1], &hexComps[2], &hexComps[3]), @"color strings must match #rrggbbaa" );

	for( int i = 0 ; i < 4 ; ++i) { 
		comps[i] = (CGFloat) ( hexComps[i] / 255.0 );	
	}

	CGColorRef cgColor;

#if TARGET_OS_OSX
	cgColor = CGColorCreateGenericRGB(comps[0], comps[1], comps[2], comps[3]);
#elif TARGET_OS_IPHONE
	cgColor = [UIColor colorWithRed: comps[0] green: comps[1] blue: comps[2] alpha: comps[3]].CGColor;
	CGColorRetain(cgColor); // returned color is autoreleased
#else
#error unsupported architecture
#endif
	
	return cgColor;
}

// result is autoreleased (or made collectable)
CGColorRef CGColorFromGenericRGBAString(NSString *genericRGBAString)
{
	return UTIL_AUTORELEASE_CF( CreateCGColorFromGenericRGBAString(genericRGBAString) );
}

@implementation ERColor

// voodoo first:
// this avoids "not KVC compliant for key"
- (id)valueForUndefinedKey:(NSString *)key {
  if ([key isEqualToString:@"CGColor"]) {
    return (id) [self CGColor];
  }

  return [super valueForUndefinedKey:key];
}

- (id)copyWithZone:(NSZone *)zone
{
	ERColor *copy = [[[self class] allocWithZone: zone] init];
	
	copy->m_CGColor = ( NULL == self->m_CGColor ) ? NULL : CGColorRetain(self->m_CGColor);
#if TARGET_OS_OSX
	copy->m_NSColor = [self->m_NSColor retain];
#endif
	copy->m_genericRGBAString = [self->m_genericRGBAString retain];
	
	return copy;
}


+ (NSSet *) keyPathsForValuesAffectingDescription
{
	return [NSSet setWithObject: @"genericRGBAString"];
}

- (NSString *) description
{
	return [NSString stringWithFormat: @"%@: genericRGBA: %@", self.class, self.genericRGBAString];
}

- (void) encodeWithCoder: (NSCoder *) encoder
{
	[encoder encodeObject: self.genericRGBAString forKey: @"genericRGBAString"];
}

- (id)initWithCoder:(NSCoder *)decoder
{
	self.genericRGBAString = [decoder decodeObjectForKey: @"genericRGBAString"];
	return self;
}

- (id) initWithGenericRGBAString: (NSString *) genericRGBAString
{
	if( nil != ( self = [super init] ) ) {
		[self setGenericRGBAString: genericRGBAString];
	}
	return self;
}

- (id) initWithCGColor: (CGColorRef) cgColor
{
	if( nil != ( self = [super init] ) ) {
		[self setCGColor: cgColor];
	}
	return self;
}

#if TARGET_OS_OSX
- (id) initWithNSColor: (NSColor *) nsColor
{
	if( nil != ( self = [super init] ) ) {
		[self setNSColor: nsColor];
	}
	return self;
}
#endif

+ (ERColor *) colorWithGenericRGBAString: (NSString *) genericRGBAString
{
	return [[[self alloc] initWithGenericRGBAString: genericRGBAString] autorelease];
}

+ (ERColor *) colorWithCGColor: (CGColorRef) cgColor
{
	return [[[self alloc] initWithCGColor: cgColor] autorelease];
}

#if TARGET_OS_OSX
+ (ERColor *) colorWithNSColor: (NSColor *) nsColor
{
	return [[[self alloc] initWithNSColor: nsColor] autorelease];
}
#endif



- (BOOL) updateGenericRGBAString: (NSString *) newGenericRGBAString
{
	if( ( nil == newGenericRGBAString && nil == m_genericRGBAString ) || ( nil != newGenericRGBAString && nil != m_genericRGBAString && [newGenericRGBAString isEqualToString: m_genericRGBAString] ) ) {
		return NO;
	}

	[self willChangeValueForKey: @"genericRGBAString"];
	NSString *tmp = m_genericRGBAString;
	m_genericRGBAString = [newGenericRGBAString copy];
	[tmp release];
	[self didChangeValueForKey: @"genericRGBAString"];
	return YES;
}


- (BOOL) updateCGColor: (CGColorRef) newCGColor
{
	if( ( NULL == newCGColor && NULL == m_CGColor ) || ( NULL != newCGColor && NULL != m_CGColor && CGColorEqualToColor(newCGColor, m_CGColor) ) ) {
		return NO;
	}
	
	[self willChangeValueForKey: @"CGColor"];
	CGColorRef tmp = m_CGColor;
	if( NULL != newCGColor ) {
		CGColorRetain( newCGColor) ;
	}
	m_CGColor = newCGColor;
	if( NULL != tmp ) {
		CGColorRelease(tmp);
	}
	[self didChangeValueForKey: @"CGColor"];
	return YES;
}

#if TARGET_OS_OSX
- (BOOL) updateNSColor: (NSColor *) newNSColor
{
	if( ( nil == newNSColor && nil == m_NSColor )  || ( nil != newNSColor && nil != m_NSColor && [newNSColor isEqual: m_NSColor] ) ) {
		return NO;
	}

	[self willChangeValueForKey: @"NSColor"];
	NSColor *tmp = m_NSColor;
	m_NSColor = [newNSColor retain];
	[tmp release];
	[self didChangeValueForKey: @"NSColor"];
	return YES;
}
#endif

- (NSString *) genericRGBAString
{
	return [[m_genericRGBAString retain] autorelease];
}

// returns a hex string without alpha value, e.g. for use in CSS
- (NSString *) genericRGBString
{
	if ([m_genericRGBAString length] < 9) return nil;
	return [m_genericRGBAString substringToIndex: 7]; // cut off alpha value
}

- (CGFloat)alphaValue {
	CGColorRef cgColor = [self CGColor];
	return CGColorGetAlpha(cgColor);
}

- (void) setGenericRGBAString: (NSString *) genericRGBAString
{
	if( NO == [self updateGenericRGBAString: genericRGBAString] ) {
		return;
	}
	
	CGColorRef cgColor = CreateCGColorFromGenericRGBAString(genericRGBAString);

	[self updateCGColor: cgColor];

#if TARGET_OS_OSX
	[self updateNSColor: (nil == cgColor) ? nil : [NSColor colorWithCIColor: [CIColor colorWithCGColor: cgColor]]];
#endif

	if( NULL != cgColor ) {
		CGColorRelease(cgColor);
	}
}

- (CGColorRef) CGColor
{
	return UTIL_AUTORELEASE_CF( UTIL_RETAIN_CF( m_CGColor ) );
}

- (void) setCGColor: (CGColorRef) cgColor
{
	if( NO == [self updateCGColor: (CGColorRef) cgColor] ) {
		return;
	}

#if TARGET_OS_OSX
	NSColor *color = (nil == cgColor) ? nil : [NSColor colorWithCIColor: [CIColor colorWithCGColor: cgColor]];
	[self updateNSColor: color];

	[self updateGenericRGBAString: GenericRGBAStringFromColor(color)];
#else
#if MAINTAINER_WARNINGS
	#warning BK: I don't know of a way to convert a CGColorRef to another colorspace on iPhone
#endif
	[self updateGenericRGBAString: (nil == cgColor) ? nil : GenericRGBAStringFromCGColor(cgColor)];
#endif
}

#if TARGET_OS_OSX
- (NSColor *) NSColor
{
	return [[m_NSColor retain] autorelease];
}

- (void) setNSColor: (NSColor *) color
{
	if( NO == [self updateNSColor: color] ) {
		return;
	}

	NSString *genericRGBAString = GenericRGBAStringFromColor(color);

	CGColorRef cgColor = NULL;

	if( color == nil ) {
		[self updateCGColor: NULL];
	} else {
		// ensure resolution of named colorspaces 
		color = [color colorUsingColorSpace: [NSColorSpace genericRGBColorSpace]];
		
		// "autoreleased"
		CGColorSpaceRef cgColorSpace = [[color colorSpace] CGColorSpace];
		if( NULL == cgColorSpace ) { // unrepresentable
			cgColor = CreateCGColorFromGenericRGBAString( genericRGBAString );
		} else {
#if MAINTAINER_WARNINGS
#warning BK: possible crasher - need to check for Named, Pattern, maybe some Custom colorspaces (which don't have float components)
#warning BK: Named should be taken care of now by above conversion

#endif
			NSInteger numComps = [color numberOfComponents];
			CGFloat comps[numComps];
			[color getComponents: comps];
			cgColor = CGColorCreate(cgColorSpace, comps);
		}
	}

	[self updateCGColor: cgColor];

	if( NULL != cgColor ) {
		CGColorRelease(cgColor);
	}

	[self updateGenericRGBAString: genericRGBAString];
}	
#endif

@end

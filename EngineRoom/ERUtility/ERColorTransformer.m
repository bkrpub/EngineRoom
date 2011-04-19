
#import <EngineRoom/ERColorTransformer.h>
#import <EngineRoom/ERColor.h>

#if TARGET_OS_OSX
#import <Cocoa/Cocoa.h>

@implementation ERColorNSColorTransformer

+ (Class)transformedValueClass { return [NSColor class]; }

+ (BOOL)allowsReverseTransformation { return YES; }

- (id)transformedValue:(id)erColor {
	return nil == erColor || NSIsControllerMarker( erColor ) ? nil : ((ERColor *)erColor).NSColor;
}

- (id)reverseTransformedValue:(id)nsColor {
	return nil == nsColor || NSIsControllerMarker(nsColor) ? nil : [ERColor colorWithNSColor: nsColor];
}
#endif

@end

@implementation ERColorCGColorTransformer

+ (Class)transformedValueClass { return [NSObject class]; }

+ (BOOL)allowsReverseTransformation { return YES; }

- (id)transformedValue:(id)erColor {
	return nil == erColor || NSIsControllerMarker( erColor ) ? nil : (id) ((ERColor *)erColor).CGColor;
}

- (id)reverseTransformedValue:(id)cgColor {
	return nil == cgColor || NSIsControllerMarker(cgColor) ? nil : [ERColor colorWithCGColor: (CGColorRef)cgColor];
}

@end

@implementation ERColorGenericRGBAStringTransformer

+ (Class)transformedValueClass { return [NSString class]; }

+ (BOOL)allowsReverseTransformation { return YES; }

- (id)transformedValue:(id)erColor {
	return nil == erColor || NSIsControllerMarker( erColor ) ? nil : ((ERColor *)erColor).genericRGBAString;
}

- (id)reverseTransformedValue:(id)genericRGBAString {
	return nil == genericRGBAString || NSIsControllerMarker(genericRGBAString) ? nil : [ERColor colorWithGenericRGBAString: genericRGBAString];
}

@end

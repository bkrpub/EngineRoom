
#import <EngineRoom/ERColorTransformer.h>
#import <EngineRoom/ERColor.h>

#if TARGET_OS_OSX
#define RETURN_WITH_CONTROLLERMARKER_CHECK(in, out) { id __in = (in); return __in == nil || NSIsControllerMarker( __in ) ? nil : (id)(out); }
#else
#define RETURN_WITH_CONTROLLERMARKER_CHECK(in, out) { id __in = (in); return __in == nil ? nil : (id)(out); }
#endif



#if TARGET_OS_OSX
#import <Cocoa/Cocoa.h>

@implementation ERColorNSColorTransformer

+ (Class)transformedValueClass { return [NSColor class]; }

+ (BOOL)allowsReverseTransformation { return YES; }

- (id)transformedValue:(id)erColor { RETURN_WITH_CONTROLLERMARKER_CHECK(erColor, ((ERColor *)erColor).NSColor); }

- (id)reverseTransformedValue:(id)nsColor { RETURN_WITH_CONTROLLERMARKER_CHECK(nsColor, [ERColor colorWithNSColor: nsColor]); }

@end

#endif

@implementation ERColorCGColorTransformer

+ (Class)transformedValueClass { return [NSObject class]; }

+ (BOOL)allowsReverseTransformation { return YES; }

- (id)transformedValue:(id)erColor { RETURN_WITH_CONTROLLERMARKER_CHECK(erColor, ((ERColor *)erColor).CGColor); }

- (id)reverseTransformedValue:(id)cgColor { RETURN_WITH_CONTROLLERMARKER_CHECK(cgColor, [ERColor colorWithCGColor: (CGColorRef)cgColor]); }

@end

@implementation ERColorGenericRGBAStringTransformer

+ (Class)transformedValueClass { return [NSString class]; }

+ (BOOL)allowsReverseTransformation { return YES; }

- (id)transformedValue:(id)erColor { RETURN_WITH_CONTROLLERMARKER_CHECK(erColor, ((ERColor *)erColor).genericRGBAString); }

- (id)reverseTransformedValue:(id)genericRGBAString { 
    RETURN_WITH_CONTROLLERMARKER_CHECK(genericRGBAString, [ERColor colorWithGenericRGBAString: genericRGBAString]); 
}

@end

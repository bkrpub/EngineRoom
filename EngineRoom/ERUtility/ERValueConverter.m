
#import "ERValueConverter.h"

#import <EngineRoom/Convenience.h>
#import <EngineRoom/ERColor.h>
#import <EngineRoom/CrossPlatform_Utilities.h>


#if NS_BLOCKS_AVAILABLE

NSString *kERValueConverterCGPointFromString                = @"NSString CGPoint NSValue";
NSString *kERValueConverterStringFromCGPoint                = @"NSValue CGPoint NSString";

ERValueConverterBlock ERValueConverterCGPointValueFromString = ^(id value, NSDictionary *valueConverters, id userInfo) 
{ return (id)[NSValue valueWithCGPoint: CGPointFromString(value)]; };

ERValueConverterBlock ERValueConverterStringFromCGPointValue = ^(id value, NSDictionary *valueConverters, id userInfo) 
{ return (id) NSStringFromCGPoint( [value CGPointValue] ); };

NSString *kERValueConverterCGSizeValueFromString            = @"NSString CGSize NSValue";
NSString *kERValueConverterStringFromCGSizeValue            = @"NSValue CGSize NSString";

ERValueConverterBlock ERValueConverterCGSizeValueFromString = ^(id value, NSDictionary *valueConverters, id userInfo) 
{ return (id)[NSValue valueWithCGSize: CGSizeFromString(value)]; };

ERValueConverterBlock ERValueConverterStringFromCGSizeValue = ^(id value, NSDictionary *valueConverters, id userInfo) 
{ return (id) NSStringFromCGSize( [value CGSizeValue] ); };

NSString *kERValueConverterCGRectValueFromString            = @"NSString CGRect NSValue";
NSString *kERValueConverterStringFromCGRectValue            = @"NSValue CGRect NSString";

ERValueConverterBlock ERValueConverterCGRectValueFromString = ^(id value, NSDictionary *valueConverters, id userInfo)
{ return (id)[NSValue valueWithCGRect: CGRectFromString(value)]; };

ERValueConverterBlock ERValueConverterStringFromCGRectValue = ^(id value, NSDictionary *valueConverters, id userInfo)
{ return (id) NSStringFromCGRect( [value CGRectValue] ); };

NSString *kERValueConverterCGAffineTransformFromString      = @"NSString CGAffineTransform NSValue";
NSString *kERValueConverterStringFromCGAffineTransform      = @"NSValue CGAffineTransform NSString";

NSString *kERValueConverterCATransform3DFromString          = @"NSString CATransform3D NSValue";
NSString *kERValueConverterStringFromCATransform3D          = @"NSValue CATransform3D NSString";

NSString *kERValueConverterERColorFromGenericRGBAString     = @"NSString(GenericRGBA) ERColor";
NSString *kERValueConverterGenericRGBAStringFromERColor     = @"ERColor NSString(GenericRGBA)";

ERValueConverterBlock ERValueConverterERColorFromGenericRGBAString = ^(id value, NSDictionary *valueConverters, id userInfo)
{ return (id) [ERColor colorWithGenericRGBAString: value]; };

ERValueConverterBlock ERValueConverterGenericRGBAStringFromERColor = ^(id value, NSDictionary *valueConverters, id userInfo)
{ return (id)[value genericRGBAString]; };

NSString *kERValueConverterCGColorFromGenericRGBAString     = @"NSString(GenericRGBA) CGColor";
NSString *kERValueConverterGenericRGBAStringFromCGColor     = @"CGColor NSString(GenericRGBA)";

ERValueConverterBlock ERValueConverterCGColorFromGenericRGBAString = ^(id value, NSDictionary *valueConverters, id userInfo)
{ return (id) [[ERColor colorWithGenericRGBAString: value] CGColor]; };

ERValueConverterBlock ERValueConverterGenericRGBAStringFromCGColor = ^(id value, NSDictionary *valueConverters, id userInfo)
{ return (id)[[ERColor colorWithCGColor: (CGColorRef) value] genericRGBAString]; };

#if TARGET_OS_OSX
NSString *kERValueConverterNSColorFromGenericRGBAString     = @"String(GenericRGBAString) NSColor";
NSString *kERValueConverterGenericRGBAStringFromNSColor     = @"NSColor String(GenericRGBAString)";

ERValueConverterBlock ERValueConverterNSColorFromGenericRGBAString = ^(id value, NSDictionary *valueConverters, id userInfo)
{ return (id) [[ERColor colorWithGenericRGBAString: value] NSColor]; };

ERValueConverterBlock ERValueConverterGenericRGBAStringFromNSColor = ^(id value, NSDictionary *valueConverters, id userInfo)
{ return (id)[[ERColor colorWithNSColor: value] genericRGBAString]; };
#endif

NSString *kERValueConverterDictionaryFromDictionary         = @"NSDictionary NSDictionary";

ERValueConverterBlock ERValueConverterDictionaryFromDictionary = ^(id value, NSDictionary *valueConverters, id userInfo) 
{ 
    NSDictionary *source = value;
    NSMutableDictionary *converted = [NSMutableDictionary dictionaryWithCapacity: [source count]];
    
	[source enumerateKeysAndObjectsUsingBlock: ^ (id key, id val, BOOL *stop) {
		id (^converter)(id value) = [valueConverters objectForKey: key] ?: [valueConverters objectForKey: NSStringFromClass([val class])];
		[converted setObject: converter ? converter(val) : val forKey: key];			
    }];
	
	return (id) converted;
};

NSString *kERValueConverterArrayFromArray                   = @"NSArray NSArray";

ERValueConverterBlock ERValueConverterArrayFromArray = ^(id value, NSDictionary *valueConverters, id userInfo) 
{ 
    NSArray *source = value;
    NSMutableArray *converted = [NSMutableArray arrayWithCapacity: [source count]];
    
	[source enumerateObjectsUsingBlock: ^ (id val, NSUInteger idx, BOOL *stop) {
		id (^converter)(id value) = [valueConverters objectForKey: NSStringFromClass([val class])];
		[converted addObject: converter ? converter(val) : val];			
    }];
	
	return (id) converted;
};

NSDictionary *ERValueConvertersByName(void)
{
    static NSString *lock = @"ERValueConvertersByNameLock";
    static NSDictionary *converters = nil;
    
    @synchronized( lock ) {
        if( nil == converters ) {
            ER_DICT(
                    kERValueConverterCGPointFromString, ERValueConverterCGPointValueFromString,
                    kERValueConverterStringFromCGPoint, ERValueConverterStringFromCGPointValue,
                    
                    kERValueConverterCGSizeValueFromString, ERValueConverterCGSizeValueFromString,
                    kERValueConverterStringFromCGSizeValue, ERValueConverterStringFromCGSizeValue,
                    
                    kERValueConverterCGRectValueFromString, ERValueConverterCGRectValueFromString,
                    kERValueConverterStringFromCGRectValue, ERValueConverterStringFromCGRectValue,
                    
                    //kERValueConverterCGAffineTransformFromString, ERValueConverterCGAffineTransformFromString,
                    //kERValueConverterStringFromCGAffineTransform, ERValueConverterStringFromCGAffineTransform,
                    
                    //kERValueConverterCATransform3DFromString, ERValueConverterCATransform3DFromString,
                    //kERValueConverterStringFromCATransform3D, ERValueConverterStringFromCATransform3D,
                    
                    kERValueConverterERColorFromGenericRGBAString, ERValueConverterERColorFromGenericRGBAString,
                    kERValueConverterGenericRGBAStringFromERColor, ERValueConverterGenericRGBAStringFromERColor,
                    
                    kERValueConverterCGColorFromGenericRGBAString, ERValueConverterCGColorFromGenericRGBAString,
                    kERValueConverterGenericRGBAStringFromCGColor, ERValueConverterGenericRGBAStringFromCGColor,
#if TARGET_OS_OSX
                    kERValueConverterNSColorFromGenericRGBAString, ERValueConverterNSColorFromGenericRGBAString,
                    kERValueConverterGenericRGBAStringFromNSColor, ERValueConverterGenericRGBAStringFromNSColor,
#endif
                    kERValueConverterDictionaryFromDictionary, ERValueConverterDictionaryFromDictionary,
                    kERValueConverterArrayFromArray, ERValueConverterArrayFromArray,
                    );
        }
    }
    
    return converters;
}

@implementation ERValueConverter

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)dealloc
{
    [super dealloc];
}

@end


#endif


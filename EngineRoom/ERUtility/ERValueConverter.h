
#import <Foundation/Foundation.h>

// this stuff is still under quarantine

#if NS_BLOCKS_AVAILABLE

typedef id (^ERValueConverterBlock)(id value, NSDictionary *valueConverters, id userInfo);

extern NSString *kERValueConverterCGPointFromString;
extern NSString *kERValueConverterStringFromCGPoint;

extern ERValueConverterBlock ERValueConverterCGPointValueFromString;
extern ERValueConverterBlock ERValueConverterStringFromCGPointValue;

extern NSString *kERValueConverterCGSizeValueFromString;
extern NSString *kERValueConverterStringFromCGSizeValue;

extern ERValueConverterBlock ERValueConverterCGSizeValueFromString;
extern ERValueConverterBlock ERValueConverterStringFromCGSizeValue;

extern NSString *kERValueConverterCGRectValueFromString;
extern NSString *kERValueConverterStringFromCGRectValue;

extern ERValueConverterBlock ERValueConverterCGRectValueFromString;
extern ERValueConverterBlock ERValueConverterStringFromCGRectValue;

extern NSString *kERValueConverterCGAffineTransformFromString;
extern NSString *kERValueConverterStringFromCGAffineTransform;

extern NSString *kERValueConverterCATransform3DFromString;
extern NSString *kERValueConverterStringFromCATransform3D;

extern NSString *kERValueConverterERColorFromGenericRGBAString;
extern NSString *kERValueConverterGenericRGBAStringFromERColor;

extern ERValueConverterBlock ERValueConverterERColorFromGenericRGBAString;
extern ERValueConverterBlock ERValueConverterGenericRGBAStringFromERColor;

extern NSString *kERValueConverterCGColorFromGenericRGBAString;
extern NSString *kERValueConverterGenericRGBAStringFromCGColor;

extern ERValueConverterBlock ERValueConverterCGColorFromGenericRGBAString;
extern ERValueConverterBlock ERValueConverterGenericRGBAStringFromCGColor;

#if TARGET_OS_OSX
extern NSString *kERValueConverterNSColorFromGenericRGBAString;
extern NSString *kERValueConverterGenericRGBAStringFromNSColor;

extern ERValueConverterBlock ERValueConverterNSColorFromGenericRGBAString;
extern ERValueConverterBlock ERValueConverterGenericRGBAStringFromNSColor;
#endif

extern NSString *kERValueConverterDictionaryFromDictionary;
extern ERValueConverterBlock ERValueConverterDictionaryFromDictionary;

extern NSString *kERValueConverterArrayFromArray;
extern ERValueConverterBlock ERValueConverterArrayFromArray;

extern NSDictionary *ERValueConvertersByName(void);


@interface ERValueConverter : NSObject {
@private
    
}

@end

#endif

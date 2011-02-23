
#import <Foundation/Foundation.h>

// this stuff is still under quarantine

#define kERValueTransformersInfoPlistKey @"ERValueTransformers"

#define kERValueTransformerKeyPrefix @"#"

#define kERValueTransformerClassKey @"#class"
//#define kERValueTransformerNameKey  @"#name"


@interface ERValueTransformer : NSValueTransformer {}

+ (void) registerSelf;

// allocates kERValueTransformerClassKey, sets remaining attributes not prefixed with #
+ (NSValueTransformer *) transformerWithDictionary: (NSDictionary *) dict error: (NSError **) outError;

+ (BOOL) registerNamedTransformers: (NSDictionary *) namedTransformers error: (NSError **) outError;

// uses mainBundle and ER bundle if bundles is nil 
+ (BOOL) registerTransformersFromBundles: (NSArray *) bundles error: (NSError **) outError;


- (void) registerWithName: (NSString *) name;

#if ERVALUETRANSFORMERAUTOREGISTRATION
+ (void) registerSelfAndSubclasses;
#endif


@end

@interface ERToNumberTransformer : ERValueTransformer {}
@end

@interface ERToStringTransformer : ERValueTransformer {}
@end


@interface ERNumberToBoolTransformer : ERToNumberTransformer {}
- (BOOL) boolForDouble: (double) value;
// no reverse support
@end

@interface ERNumberToDoubleTransformer : ERToNumberTransformer {}
- (double) doubleForDouble: (double) value;

// override allowsReverseTransformation to use this
- (double) reverseDoubleForDouble: (double) value;

@end

@interface ERExpressionTransformer : ERValueTransformer {
	NSPredicate *m_predicate;
	NSExpression *m_expression;
	NSExpression *m_alternateExpression;
	NSPredicate *m_reversePredicate;
	NSExpression *m_reverseExpression;
	NSExpression *m_reverseAlternateExpression;
}

@property(nonatomic, retain) id predicate;
@property(nonatomic, retain) id expression;
@property(nonatomic, retain) id alternateExpression;

@property(nonatomic, retain) id reversePredicate;
@property(nonatomic, retain) id reverseExpression;
@property(nonatomic, retain) id reverseAlternateExpression;

// use only expressions which form a valid predicate in the form: ( expression ) = 0 
- (NSExpression *) expressionWithString: (NSString *) expressionString;


@end


@interface ERNumberExpressionTransformer : ERExpressionTransformer {}
@end

@interface ERStringExpressionTransformer : ERExpressionTransformer {}
@end


#if 0
@interface ERPredicateEvaluatorTransformer : ERToNumberTransformer {
    NSPredicate *m_predicate;
}

+ (void) registerWithName: (NSString *) name predicate: (NSPredicate *) predicate;
+ (void) registerWithName: (NSString *) name predicateFormat: (NSString *) format, ...;

- (id) initWithPredicate: (NSPredicate *) predicate;
- (id) initWithPredicateFormat: (NSString *) format, ...;

@end

@interface ERExpressionEvaluatorTransformer : ERValueTransformer {
	NSExpression *m_expression;
}

+ (void) registerWithName: (NSString *) name expression: (NSExpression *) expression;

// see initWithExpressionFormat
+ (void) registerWithName: (NSString *) name expressionFormat: (NSString *) format, ...;

- (id) initWithExpression: (NSExpression *) expression;

// based on a great hack by Dave De Long
// see http://funwithobjc.tumblr.com/post/1553469975/abusing-nspredicate
// parses it as "yourstuff = 0" and takes the left side
// some expressions don't work, i.e. an identifier without a comparison
- (id) initWithExpressionFormat: (NSString *) format, ...;

- (id) initWithExpressionFormat: (NSString *) format arguments: (va_list) args;

@end
#endif


@interface ERLogarithmicTransformer : ERNumberToDoubleTransformer {
    double power;
}

+ (void) registerWithPower: (double) power forName: (NSString *) name;

- (id) initWithPower: (double) power;

@end

@interface ERSignInverterTransformer : ERNumberToDoubleTransformer {}
@end

@interface ERAbsoluteValueTransformer : ERNumberToDoubleTransformer {}
@end

@interface ERLocalizerTransformer : ERToStringTransformer {}
@end

// useful for arrays of NSDictionaryControllerKeyValuePair,
// use it i.e. to bind the content of a popup through a VT,
// NOT the contentValues ! use localizedKey in the contentValues
@interface ERKeyValuePairKeyLocalizerTransformer : ERValueTransformer {}
@end

// useful if you want to bind i.e. a TextField to a controllers selectedObjects
// for debugging purposes and you are tired of seeing Proxy objects or (<null>, <null>)
@interface ERArrayWithArrayTransformer : ERValueTransformer {}
@end

#if ER_NOT_YET

@interface ERArrayOfObjectsToPropertyListTransformer : ERValueTransformer {}
@end

#endif

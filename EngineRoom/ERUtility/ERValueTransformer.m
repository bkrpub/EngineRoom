
#import "ERValueTransformer.h"

#import "Convenience.h"
#import "logpoints_default.h"
#import "logpoints_nslog.h"

#if ERVALUETRANSFORMERAUTOREGISTRATION

#import <objc/objc-runtime.h>

/* think: palette with editable  predicates, mini language, ...  on instances of transformers */

/*
static void __attribute__((constructor)) construct_ERValueTransformer(void) 
{
    lpkdebugf("valueTransformerSetup", "ERValueTransformer setup");
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    [ERValueTransformer registerSelfAndSubclasses];
    [pool release];
    lpkdebugf("valueTransformerSetup", "ERValueTransformer setup done");
}
*/
#endif 


@implementation ERValueTransformer

+ (Class) transformedValueClass { 
    return [NSObject class];
}

+ (BOOL)allowsReverseTransformation { return NO; }

- (id) reverseTransformedValue: (id) value
{
	lpktrace("valueTransformerTest", value);
    return value;
}

- (id) transformedValue: (id) value { 
	lpktrace("valueTransformerTest", value);
    return value;
}

- (void) registerWithName: (NSString *) name
{
        lpkdebugf("valueTransformerSetup", "%@ registers as %@ (class: %@)", self, name, NSStringFromClass([[self class] transformedValueClass]));
        [[self class] setValueTransformer: self forName: name];    
}

+ (void) registerSelf
{
    NSString *transformerClassName = NSStringFromClass(self);
    
    NSString *shortName = transformerClassName;
    
    if( [transformerClassName hasSuffix: @"ValueTransformer"] )
        shortName = [shortName substringToIndex: [shortName length] - (sizeof("ValueTransformer")-1)];
    else
        if( [transformerClassName hasSuffix: @"Transformer"] )
            shortName = [shortName substringToIndex: [shortName length] - (sizeof("Transformer")-1)];
             
    [[[[self alloc] init] autorelease] registerWithName: shortName];
}


#define ER_SET_NSERROR_POSIX(errorPtr, code, reasonFormat, ...) ER_SET_NSERROR_REASON((errorPtr), NSPOSIXErrorDomain, (code), reasonFormat, ## __VA_ARGS__) 
#define ER_CHECK_NSERROR_POSIX(assertion, errorPtr, code, reasonFormat, ...) ER_CHECK_NSERROR_REASON((assertion), (errorPtr), NSPOSIXErrorDomain, (code), reasonFormat, ## __VA_ARGS__) 
#define ER_CHECK_NSERROR_POSIX_RETURN_NO(assertion, errorPtr, code, reasonFormat, ...) ER_CHECK_NSERROR_REASON_RETURN_NO((assertion), (errorPtr), NSPOSIXErrorDomain, (code), reasonFormat, ## __VA_ARGS__) 
#define ER_CHECK_NSERROR_POSIX_RETURN_NIL(assertion, errorPtr, code, reasonFormat, ...) ER_CHECK_NSERROR_REASON_RETURN_NIL((assertion), (errorPtr), NSPOSIXErrorDomain, (code), reasonFormat, ## __VA_ARGS__) 


+ (NSValueTransformer *) transformerWithDictionary: (NSDictionary *) dict error: (NSError **) outError
{
	NSString *vtClassName = [dict objectForKey: kERValueTransformerClassKey];

	ER_CHECK_NSERROR_POSIX_RETURN_NIL( 0 != [vtClassName length], outError, EINVAL, @"errorVTDefinition %@ has no '%@' key", dict, kERValueTransformerClassKey);

	Class vtClass = NSClassFromString(vtClassName);

	ER_CHECK_NSERROR_POSIX_RETURN_NIL( Nil != vtClass, outError, ENOENT, @"errorClassNotFoundForVTDefinition %@", dict);
	
	NSValueTransformer *vt = [[[vtClass alloc] init] autorelease];
	
	ER_CHECK_NSERROR_POSIX_RETURN_NIL( nil != vt, outError, ENOSYS, @"errorCouldNotCreateVT %@", dict);
	
	for(NSString *key in dict) {
		if( YES == [key hasPrefix: kERValueTransformerKeyPrefix] ) {
			continue;
		}
		
		[vt setValue: [dict objectForKey: key] forKey: key];
	}

	return vt;
}

+ (BOOL) registerNamedTransformers: (NSDictionary *) namedTransformers error: (NSError **) outError
{
	for(NSString *vtName in namedTransformers) {
		id transformerDescription = [namedTransformers objectForKey: vtName];
		
		ER_CHECK_NSERROR_POSIX_RETURN_NO( 0 != [vtName length], outError, EINVAL, @"errorVTDefinition %@ has no name", transformerDescription);

		NSValueTransformer *vt = [NSValueTransformer valueTransformerForName: vtName];
		
		ER_CHECK_NSERROR_POSIX_RETURN_NO( nil == vt, outError, EEXIST, @"errorVTNameAlreadyExists '%@'", vtName);



		if( [transformerDescription isKindOfClass: [NSString class]] ) {
			transformerDescription = ER_DICT(
												kERValueTransformerClassKey,
												NSStringFromClass([ERNumberExpressionTransformer class]),
												@"predicate", 
												transformerDescription
			);
		}
			
		vt = [self transformerWithDictionary: transformerDescription error: outError];
 
		if( nil == vt ) {
			return NO;
		}
		
		[NSValueTransformer setValueTransformer: vt forName: vtName];
	}
	
	return YES;
}

+ (BOOL) registerTransformersFromBundles: (NSArray *) bundlesToSearch error: (NSError **) outError
{
	if( nil == bundlesToSearch ) {
		bundlesToSearch = ER_ARRAY([NSBundle bundleForClass: self], [NSBundle mainBundle]);
	}

	for(NSBundle *bundle in bundlesToSearch) {
		NSDictionary *namedTransformers = [bundle objectForInfoDictionaryKey: kERValueTransformersInfoPlistKey];
		if( nil != namedTransformers ) {
			lpkdebug("valueTransformerSetup", [bundle bundleIdentifier], namedTransformers);
			if( NO == [ERValueTransformer registerNamedTransformers: [bundle objectForInfoDictionaryKey: kERValueTransformersInfoPlistKey] error: outError] ) {
				return NO;
			}
		}
	}

	return YES;
}

#if ERVALUETRANSFORMERAUTOREGISTRATION

+ (void) registerSelfAndSubclasses
{
    int numClasses = 0, newNumClasses = objc_getClassList(NULL, 0);
    Class *classes = NULL;
    while (numClasses < newNumClasses) {
        numClasses = newNumClasses;
        classes = realloc(classes, sizeof(Class) * numClasses);
        newNumClasses = objc_getClassList(classes, numClasses);
    }

    if( classes ) {
        Class ownClass = [self class];

        SEL abstractTestSelector = @selector(transformedValue:);
        IMP abstractTestIMP = [self instanceMethodForSelector: abstractTestSelector];

        int i;
        for(i = 0 ; i < numClasses ; ++i ) {

            Class transformerClass = classes[i];
            Class tmp = transformerClass;

            while( tmp && tmp != ownClass ) { 
                tmp = tmp->super_class;
            }
            
            if( tmp != ownClass ) // 
                continue;
                
            if( abstractTestIMP == [transformerClass instanceMethodForSelector: abstractTestSelector] ) {
                lpkdebugf("valueTransformerSetup", "%@ does not implement %@", NSStringFromClass(transformerClass), NSStringFromSelector(abstractTestSelector));
                continue;
            }

            [transformerClass registerSelf];
        }
        
        free(classes);    
    }
}
#endif
/* ERVALUETRANSFORMERAUTOREGISTRATION */

@end

@implementation ERToStringTransformer

+ (Class) transformedValueClass { 
    return [NSString self]; 
}

@end

@implementation ERToNumberTransformer

+ (Class) transformedValueClass { 
    return [NSNumber self]; 
}

@end


@implementation ERNumberToBoolTransformer

static NSNumber *number_bool_yes = nil, *number_bool_no = nil;

+ (void)initialize
{
	if (self == [ERNumberToBoolTransformer class]) {
        number_bool_yes = [[NSNumber alloc] initWithBool: YES];
        number_bool_no = [[NSNumber alloc] initWithBool: NO];
	}
}

- (BOOL) boolForDouble: (double) value { return value != 0.0 ? YES : NO; }

- (id) transformedValue: (id) value { 
    id result = value ? [self boolForDouble: [value doubleValue]] ? number_bool_yes : number_bool_no : nil;
	lpkdebug("valueTransformation", value, result);
	return result;
}

@end

@implementation ERNumberToDoubleTransformer

- (double) doubleForDouble: (double) value { 
    (void) value;
    lpkassertf("valueTransformerError", nil, "abstract");
    return 0.0;
}

- (double) reverseDoubleForDouble: (double) value { 
    (void) value;
	lpkassertf("valueTransformerError", nil, "abstract");
    return 0.0;
}

- (id) transformedValue: (id) value {

	id result = nil;
	
    if( nil != value ) {
     
		if( ! [value isKindOfClass: [NSNumber class]] ) {
			lpkerror("valueTransformerError", "defined only for numeric values - returning nil", value, [value class]);
			return nil;
		}
		
		result = [NSNumber numberWithDouble: [self doubleForDouble: [value doubleValue]]];
	}
		
	lpkdebug("valueTransformation", value, result);
    return result;
}

- (id) reverseTransformedValue: (id) value { 

	id result = nil;
	
    if( nil != value ) {
		
		if( ! [value isKindOfClass: [NSNumber class]] ) {
			lpkerror("valueTransformerError", "defined only for numeric values - returning nil - Hint: use formatters on textfields, otherwise you may run into decimal separator localization issues", value, [value class]);
			return nil;
		}
		
		result = [NSNumber numberWithDouble: [self reverseDoubleForDouble: [value doubleValue]]];
    }
		
	lpkdebug("valueTransformation", value, result);
	
    return result;
}

@end

@implementation ERExpressionTransformer

@synthesize predicate = m_predicate;
@synthesize expression = m_expression;
@synthesize alternateExpression = m_alternateExpression;
@synthesize reversePredicate = m_reversePredicate;
@synthesize reverseExpression = m_reverseExpression;
@synthesize reverseAlternateExpression = m_reverseAlternateExpression;

+ (BOOL)allowsReverseTransformation { return YES; }

// based on a great, simple hack by Dave De Long
// see http://funwithobjc.tumblr.com/post/1553469975/abusing-nspredicate
// parses it as "yourstuff = 0" and takes the left side
// (imposes some restrictions, see BNF description in Predicate Programming Guide)
- (NSExpression *) expressionWithString: (NSString *) expressionString
{
	NSString *fakePredicateFormat = [@"( " stringByAppendingString: [expressionString stringByAppendingString: @" ) = 0 "]];
	lpdebug(fakePredicateFormat);
	
	NSPredicate *predicate = [NSPredicate predicateWithFormat: fakePredicateFormat];
	lpdebug(predicate);
	
	NSExpression *expression = [(NSComparisonPredicate *)predicate leftExpression];

	return expression;
}


- (void) setPredicate: (id) predicate
{
	if([predicate isKindOfClass: [NSString class]]) {
		predicate = [NSPredicate predicateWithFormat: predicate];
	}

	[m_predicate autorelease];
	m_predicate = [predicate retain];
}

- (void) setExpression: (id) expression
{
	if([expression isKindOfClass: [NSString class]]) {
		expression = [self expressionWithString: expression];
	}
	
	[m_expression autorelease];
	m_expression = [expression retain];
}

- (void) setAlternateExpression: (id) alternateExpression
{
	if([alternateExpression isKindOfClass: [NSString class]]) {
		alternateExpression = [self expressionWithString: alternateExpression];
	}
	
	[m_alternateExpression autorelease];
	m_alternateExpression = [alternateExpression retain];
}

- (void) setReversePredicate: (id) predicate
{
	if([predicate isKindOfClass: [NSString class]]) {
		predicate = [NSPredicate predicateWithFormat: predicate];
	}
	
	[m_reversePredicate autorelease];
	m_reversePredicate = [predicate retain];
}

- (void) setReverseExpression: (id) expression
{
	if([expression isKindOfClass: [NSString class]]) {
		expression = [self expressionWithString: expression];
	}
	
	[m_reverseExpression autorelease];
	m_reverseExpression = [expression retain];
}

- (void) setReverseAlternateExpression: (id) alternateExpression
{
	if([alternateExpression isKindOfClass: [NSString class]]) {
		alternateExpression = [self expressionWithString: alternateExpression];
	}
	
	[m_reverseAlternateExpression autorelease];
	m_reverseAlternateExpression = [alternateExpression retain];
}


- (id) transformValue: (id) value predicate: (NSPredicate *) predicate expression: (NSExpression *) expression alternateExpression: (NSExpression *) alternateExpression
{	
	BOOL predicateResult = YES;
	id result = nil;

	if( nil == value ) {
		lpkdebug("valueTransformer", "nilValue");
		return nil;
	}
	
	static NSMutableDictionary *staticBindings = nil;
	
	if( nil == staticBindings ) {
		staticBindings = [ER_DICT(
								 @"NSString", [NSString class],
								 @"NSNumber", [NSNumber class],
								 @"NSDate", [NSDate class],
								 @"NSApp", NSApp,								 
								 ) mutableCopy];
	}
	
	if( nil != predicate ) {
		predicateResult = [predicate evaluateWithObject: value substitutionVariables: staticBindings];
	}
	
	if( nil == expression && nil == alternateExpression ) {
		result = [NSNumber numberWithBool: predicateResult];
	} else {
		
		NSExpression *selectedExpression = predicateResult ? expression : alternateExpression;
		
		if ( nil == selectedExpression ) {
			result = [NSNumber numberWithBool: predicateResult ? YES : NO];
		} else {
			result = [selectedExpression expressionValueWithObject: value context: staticBindings];
		}
	}
	
    return result;
}


- (id) transformedValue: (id) value
{	
	return [self transformValue: value predicate: self.predicate expression: self.expression alternateExpression: self.alternateExpression];
}

- (id)reverseTransformedValue:(id)value;
{
	return [self transformValue: value predicate: self.reversePredicate expression: self.reverseExpression alternateExpression: self.reverseAlternateExpression];
}

- (NSString *) description
{
    return [NSString stringWithFormat: @"%@(predicate: %@ expression: %@ alternateExpression: %@)", 
			NSStringFromClass([self class]), 
			self.predicate, self.expression, self.alternateExpression,
			self.reversePredicate, self.reverseExpression, self.reverseAlternateExpression
			];
}


- (void) dealloc
{
    [m_predicate release];
	[m_expression release];
	[m_alternateExpression release];
    [m_reversePredicate release];
	[m_reverseExpression release];
	[m_reverseAlternateExpression release];
    [super dealloc];
}


@end

@implementation ERNumberExpressionTransformer

+ (Class) transformedValueClass
{
	return [NSNumber class];
}

- (id) transformedValue: (id) value
{
	id result = [super transformedValue: value];

	if( NO == [result isKindOfClass: [NSNumber class]]) {
		result = [result respondsToSelector: @selector(stringValue)] ? [result stringValue] : [result description];
		result = [NSNumber numberWithDouble: [result doubleValue]];
	}
		
	return result;
}

@end

@implementation ERStringExpressionTransformer

+ (Class) transformedValueClass
{
	return [NSString class];
}

- (id) transformedValue: (id) value
{
	id result = [super transformedValue: value];

	if( NO == [result isKindOfClass: [NSString class]]) {
		result = [result respondsToSelector: @selector(stringValue)] ? [result stringValue] : [result description];
	}
		
	return result;
}

@end


#if 0
@implementation ERPredicateEvaluatorTransformer

+ (void) registerWithName: (NSString *) name predicate: (NSPredicate *) predicate;
{
    [[[[self alloc] initWithPredicate: predicate] autorelease] registerWithName: name];
}

+ (void) registerWithName: (NSString *) name predicateFormat: (NSString *) format, ...;
{
	va_list args;
	va_start(args, format);
    [[[[self alloc] initWithPredicate: [NSPredicate predicateWithFormat: format arguments: args]] autorelease] registerWithName: name];
	va_end(args);
}

- (id) initWithPredicate: (NSPredicate *) predicate
{
    if( ( self = [super init] ) ) {
		lpdebug(predicate);
        m_predicate = [predicate retain];
    }
    return self;
}

- (id) initWithPredicateFormat: (NSString *) format, ...;
{
	va_list args;
	va_start(args, format);
	lpdebug(format);
    self = [self initWithPredicate: [NSPredicate predicateWithFormat: format arguments: args]];
	va_end(args);
	return self;
}

- (void) dealloc
{
    [m_predicate release];
    [super dealloc];
}


+ (void) registerSelf 
{
    [self registerWithName: @"ERAlwaysTrue" predicate: [NSPredicate predicateWithValue: YES]];
    [self registerWithName: @"ERAlwaysFalse" predicate: [NSPredicate predicateWithValue: NO]];
	
    [self registerWithName: @"ERIsZero" predicateFormat: @"SELF == 0"];
    [self registerWithName: @"ERIsNotZero" predicateFormat: @"SELF != 0"];
    [self registerWithName: @"ERIsSmallerZero" predicateFormat: @"SELF < 0"];
    [self registerWithName: @"ERIsGreaterZero" predicateFormat: @"SELF > 0"];
    [self registerWithName: @"ERIsSmallerEqualZero" predicateFormat: @"SELF <= 0"];
    [self registerWithName: @"ERIsGreaterEqualZero" predicateFormat: @"SELF >= 0"];
	
    [self registerWithName: @"ERIsOne" predicateFormat: @"SELF == 1"];
    [self registerWithName: @"ERIsNotOne" predicateFormat: @"SELF != 1"];
	
    [self registerWithName: @"ERIsGreaterOne" predicateFormat: @"SELF > 1"];
    [self registerWithName: @"ERIsSmallerTwo" predicateFormat: @"SELF < 2"];
	
}

- (NSString *) description
{
    return [NSString stringWithFormat: @"%@(predicateFormat: %@)", NSStringFromClass([self class]), [m_predicate predicateFormat]];
}

- (id) transformedValue: (id) value
{	
/*
	if( ! [value isKindOfClass: [NSNumber class]] ) {
	lpkerror("valueTransformerError", "defined only for numeric values - returning nil", value, [value class]);
      return nil;
    }
*/
 
	id result = [NSNumber numberWithBool: [m_predicate evaluateWithObject: value]];
		
	lpkdebug("valueTransformation", value, result);	

    return result;
}
@end

@implementation ERExpressionEvaluatorTransformer

+ (void) registerWithName: (NSString *) name expression: (NSExpression *) expression
{
    [[[[self alloc] initWithExpression: expression] autorelease] registerWithName: name];	
}

+ (void) registerWithName: (NSString *) name expressionFormat: (NSString *) format, ...
{
	va_list args;
	va_start(args, format);
    [[[[self alloc] initWithExpressionFormat: format arguments: args] autorelease] registerWithName: name];
	va_end(args);
}

- (id) initWithExpression: (NSExpression *) expression
{
    if( ( self = [super init] ) ) {
		lpdebug(expression);
        m_expression = [expression retain];
    }
    return self;		
}

// based on a great hack by Dave De Long
// see http://funwithobjc.tumblr.com/post/1553469975/abusing-nspredicate
// parses it as "yourstuff = 0" and takes the left side
// some expressions don't work, i.e. an identifier without a comparison
- (id) initWithExpressionFormat: (NSString *) format arguments: (va_list) args
{
	NSString *fakePredicateFormat = [@"( " stringByAppendingString: [format stringByAppendingString: @" ) = 0 "]];
	lpdebug(fakePredicateFormat);
	
	NSPredicate *predicate = [NSPredicate predicateWithFormat: fakePredicateFormat arguments: args];
	lpdebug(predicate);
	
	NSExpression *expression = [(NSComparisonPredicate *)predicate leftExpression];

	return [self initWithExpression: expression];
}

- (id) initWithExpressionFormat: (NSString *) format, ...
{
	va_list args;
	va_start(args, format);
	lpdebug(format);
	self = [self initWithExpressionFormat: format arguments: args];
	va_end(args);
	return self;	
}

- (void) dealloc
{
    [m_expression release];
    [super dealloc];
}

- (NSString *) description
{
    return [NSString stringWithFormat: @"%@(expression: %@)", NSStringFromClass([self class]), m_expression];
}

+ (void) registerSelf 
{
    [self registerWithName: @"ERMultiplyBy10" expressionFormat: @"SELF * 10"];
}

- (id) transformedValue: (id) value
{
	static NSMutableDictionary *staticBindings = nil;
	
	if( nil == staticBindings ) {
		staticBindings = [ERDICT(
						  @"NSString", [NSString class],
 						  @"NSNumber", [NSNumber class],
  						  @"NSDate", [NSDate class],
  						  @"NSApp", NSApp,								 
								 ) mutableCopy];
		lpkdebug("valueTransformerSetup", staticBindings);
	}
	
	id result = [m_expression expressionValueWithObject: value context: staticBindings];
//#warning move NSData (and NSError) test into LogPoints
	NSString *debugValue = [value isKindOfClass: [NSData class]] ? [NSString stringWithFormat: @"[Data, %ld bytes]", [(NSData*)value length]] : [value description];
	lpkdebug("valueTransformation", debugValue, result);	
	return result;
}

@end
#endif

@implementation NSNumber ( ERExpressionExtensions )

- (id) er_eq: (id) comparee
{
	return [NSNumber numberWithBool: [self doubleValue] == [comparee doubleValue]];
}

- (id) er_ne: (id) comparee
{
	return [NSNumber numberWithBool: [self doubleValue] != [comparee doubleValue]];
}

- (id) er_gt: (id) comparee
{
	return [NSNumber numberWithBool: [self doubleValue] > [comparee doubleValue]];
}

- (id) er_lt: (id) comparee
{
	return [NSNumber numberWithBool: [self doubleValue] < [comparee doubleValue]];
}

- (id) er_ge: (id) comparee
{
	return [NSNumber numberWithBool: [self doubleValue] >= [comparee doubleValue]];
}

- (id) er_le: (id) comparee
{
	return [NSNumber numberWithBool: [self doubleValue] <= [comparee doubleValue]];
}

- (id) er_ifElse:(id) ifTrue : (id) ifFalse
{
	return [self boolValue] ? ifTrue : ifFalse;
}

- (id) er_formatDouble: (id) formatString 
{
	return [NSString stringWithFormat: formatString, [self doubleValue]];
}

@end



@implementation ERLogarithmicTransformer

+ (void) registerWithPower: (double) power forName: (NSString *) name
{
    [[[[self alloc] initWithPower: power] autorelease] registerWithName: name];
}

+ (void) registerSelf 
{
    /* the reverse instances are registered with negative powers */
    [self registerWithPower: 2.0 forName: @"ERLog2"];
    [self registerWithPower: -2.0 forName: @"ERPow2"];
    [self registerWithPower: 10.0 forName: @"ERLog10"];
    [self registerWithPower: -10.0 forName: @"ERPow10"];
    [self registerWithPower: exp(1) forName: @"ERLogE"];
    [self registerWithPower: -exp(1) forName: @"ERPowE"];
}

- (id) initWithPower: (double) aPower
{
    if( ( self = [super init] ) ) {
        power = aPower;
    }
    return self;
}

- (NSString *) description
{
    return [NSString stringWithFormat: @"%@(power: %f)", NSStringFromClass([self class]), power];
}

+ (BOOL)allowsReverseTransformation { return YES; }

- (double) doubleForDouble: (double) value {
    return power < 0 ? pow(-power, value) : ( value == 0.0 ? 0.0 : log(value)/log(power) ); 
}

- (double) reverseDoubleForDouble: (double) value { 
    return power > 0 ? pow(power, value) : ( value == 0.0 ? 0.0 : log(value)/log(-power) ); 
}

@end

@implementation ERSignInverterTransformer : ERNumberToDoubleTransformer

+ (BOOL)allowsReverseTransformation { return YES; }

- (double) doubleForDouble: (double) value { return value == 0.0 ? 0.0 : -value; }

- (double) reverseDoubleForDouble: (double) value { return [self doubleForDouble: value]; }

@end

@implementation ERAbsoluteValueTransformer : ERNumberToDoubleTransformer

- (double) doubleForDouble: (double) value { return value >= 0.0 ? value : -value; }

@end

@implementation ERLocalizerTransformer

- (id) transformedValue: (id) value
{
	static NSString *marker = @"!L_NIL";

	NSString *key = [value respondsToSelector: @selector(stringValue)] ? [value stringValue] : value;

	id result = marker;
	
    if( nil != key ) {

		result = [[NSBundle mainBundle] localizedStringForKey: key value: marker table: nil];

		if( marker == result ) {
			result = [@"!L_" stringByAppendingString: key];
		}
	}

    lpkdebug("valueTransformation", value, result);

    return result;
}

@end

@implementation ERKeyValuePairKeyLocalizerTransformer

+ (Class) transformedValueClass { 
    return [NSArray self]; 
}

- (id) transformedValue: (id) aValue
{
	static NSString *marker = @"!L_NIL";

	if( nil == aValue ) 
		return nil;

	NSArray *value = aValue;
	
	NSUInteger count = [value count];
	NSMutableArray *localized = [NSMutableArray arrayWithCapacity: count];

	NSUInteger i;
	for( i = 0 ; i < count ; ++i ) {
		id pair = [value objectAtIndex: i];
		
		NSString *pairKey = [pair valueForKey: @"key"];
		NSString *pairValue = [pair valueForKey: @"value"];

		NSString *localizedPairKey = [[NSBundle mainBundle] localizedStringForKey: pairKey value: marker table: nil];		

		if( marker == localizedPairKey ) 
			localizedPairKey = [@"!L_" stringByAppendingString: pairKey];
		
		[localized addObject: [NSDictionary dictionaryWithObjectsAndKeys: localizedPairKey, @"localizedKey", pairKey, @"key", pairValue, @"value", nil]];
	}

    lpkdebug("valueTransformation", value, localized);

    return localized;
}

@end


@implementation ERArrayWithArrayTransformer

+ (Class) transformedValueClass { 
    return [NSArray self]; 
}

- (id) transformedValue: (id) value
{
	if( nil == value ) 
		return nil;

	NSMutableArray *newArray = [NSArray arrayWithArray: value];

    lpkdebug("valueTransformation", value, newArray);

    return newArray;
}

@end

#if ER_NOT_YET

@implementation ERArrayOfObjectsToPropertyListTransformer

+ (Class) transformedValueClass { 
    return [NSArray self]; 
}

+ (BOOL)allowsReverseTransformation { return YES; }

- (id) transformedValue: (id) value
{
	if( nil == value ) 
		return nil;
		
	NSUInteger count = [value count];
	NSUInteger i;

	NSMutableArray *newArray = [NSMutableArray arrayWithCapacity: count];

	for( i = 0 ; i < count ; ++i ) {
		id obj = [value objectAtIndex: i];
		NSMutableDictionary *plist = [[obj propertyList] mutableCopy];
		[plist setObject: NSStringFromClass([obj class]) forKey: @"_className"];
		[newArray addObject: plist];
		[plist release];
	}

    lpkdebug("valueTransformation", value, newArray);

    return newArray;
}

- (id) reverseTransformedValue: (id) value
{

	if( nil == value ) 
		return nil;

	NSUInteger count = [value count];
	NSUInteger i;

	NSMutableArray *newArray = [NSMutableArray arrayWithCapacity: count];

	for( i = 0 ; i < count ; ++i ) {
		NSMutableDictionary *plist = [[value objectAtIndex: i] mutableCopy];
		NSString *className = [plist valueForKey: @"_className"];
		[plist removeObjectForKey: @"_className"];
		[newArray addObject: [NSClassFromString(className) instanceWithPropertyList: plist]];
		[plist release];
	}

    lpkdebug("valueTransformation", value, newArray);

    return newArray;

}

@end

#endif
/* ER_NOT_YET */





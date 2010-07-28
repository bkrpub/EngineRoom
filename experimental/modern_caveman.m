#import <Foundation/Foundation.h>

#import "DebugUnarchiver.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <sys/time.h>


#if __CHAR_UNSIGNED__
#define CAVEMAN_UNQUALIFIED_CHAR unsigned char
#define CAVEMAN_UNQUALIFIED_CHAR_FORMAT "u"
#else
#define CAVEMAN_UNQUALIFIED_CHAR signed char
#define CAVEMAN_UNQUALIFIED_CHAR_FORMAT "d"
#endif

#define cavemanTypeIs(v,what)                   (__builtin_types_compatible_p(__typeof__(v), what) )
#define cavemanTypeIs_opt_const(v,what)         ( cavemanTypeIs((v), what) || cavemanTypeIs((v), const what) )
#define cavemanTypeIs_opt_volatile(v,what)      ( cavemanTypeIs_opt_const((v), what) || cavemanTypeIs_opt_const((v), volatile what) )
#define cavemanTypeIs_signed(v,what)            cavemanTypeIs_opt_volatile((v), what)
#define cavemanTypeIs_unsigned(v,what)          cavemanTypeIs_opt_volatile((v), unsigned what)
#define cavemanTypeIs_opt_unsigned(v,what)      ( cavemanTypeIs_signed((v), what) || cavemanTypeIs_unsigned((v), what) )
#define cavemanTypeIs_opt_long(v,what)          ( cavemanTypeIs_opt_unsigned((v), what) || cavemanTypeIs_opt_unsigned((v), long what) )
#define cavemanTypeIs_opt_longlong(v,what)      ( cavemanTypeIs_opt_long((v), what) || cavemanTypeIs_opt_long((v), long what) )

#define cavemanTypeIs_int(v,what)           ( cavemanTypeIs_opt_unsigned((v), short what) ||  cavemanTypeIs_opt_unsigned((v), what) ||  cavemanTypeIs_opt_unsigned((v), long what) ||  cavemanTypeIs_opt_unsigned((v), long long what) )

#define cavemanTypeIs_intptr(v,what)        cavemanTypeIs_int((v), what *)

/* unused */
#define cavemanTypeIs_array(v)         ( cavemanTypeIs_int((v), int[]) || cavemanTypeIs_opt_volatile((v), char[]) )

#define cavemanFormatValue(v, label) ({ \
      struct __cmBadType { int dummy; } __cmBadType = { 0 }; /* used to generate a halfway decent error message at compile time */  \
      __typeof__ (v) __cm = (v) ; \
    void *cavemanReturn = __builtin_choose_expr( cavemanSupportedType( v ), (void *) 0, __cmBadType ); \
    if( NULL != cavemanReturn )  { \
      cavemanReturn = cavemanFormat("unknown type - should never happen - must be caught by line above"); \
    } else { \
      cavemanFormatCTypes(v, __cm, label ); \
      cavemanFormatObjCTypes(v, __cm, label); \
    } \
    cavemanReturn ? cavemanReturn : cavemanFormat("a value %s has its type declared as caveman-supported but there is no formatter for it", #v); \
})

#ifndef cavemanSupportedUserCType
#define cavemanSupportedUserCType(value) 0
#endif

#ifndef cavemanFormatUserCTypes
#define cavemanFormatUserCTypes(value, localvalue, label) /**/
#endif

#define cavemanSupportedCType(v) ( cavemanSupportedCArrayType(v) || cavemanSupportedCNonArrayType(v) )

#define cavemanSupportedCArrayType(v) ( \
    cavemanTypeIs_opt_volatile( (v), char [] ) || \
    cavemanTypeIs_opt_volatile( (v), int [] ) || \
    0 )

#define cavemanSupportedCNonArrayType(v) ( \
    cavemanSupportedUserCType(v) || \
    cavemanTypeIs_opt_volatile( (v), unsigned char ) || \
    cavemanTypeIs_opt_volatile( (v), unsigned char *) || \
    cavemanTypeIs_opt_volatile( (v), unsigned char **) || \
    cavemanTypeIs_opt_volatile( (v), unsigned char ***) || \
    cavemanTypeIs_opt_volatile( (v), signed char ) || \
    cavemanTypeIs_opt_volatile( (v), signed char *) || \
    cavemanTypeIs_opt_volatile( (v), signed char **) || \
    cavemanTypeIs_opt_volatile( (v), signed char ***) || \
    cavemanTypeIs_opt_volatile( (v), char ) /* != signed char && != unsigned char :-) */ || \
    cavemanTypeIs_opt_volatile( (v), char *) || \
    cavemanTypeIs_opt_volatile( (v), char **) || \
    cavemanTypeIs_opt_volatile( (v), char ***) || \
    cavemanTypeIs_opt_unsigned( (v), short) || \
    cavemanTypeIs_opt_unsigned( (v), int) || \
    cavemanTypeIs_opt_unsigned( (v), long) || \
    cavemanTypeIs_opt_unsigned( (v), long long) || \
    cavemanTypeIs_intptr( (v), int) || /* handles short, int, long, long long */  \
    cavemanTypeIs_intptr( (v), int *) || \
    cavemanTypeIs_intptr( (v), int **) || \
    cavemanTypeIs_opt_volatile( (v), float ) || \
    cavemanTypeIs_opt_volatile( (v), float *) || \
    cavemanTypeIs_opt_volatile( (v), float **) || \
    cavemanTypeIs_opt_volatile( (v), float ***) || \
    cavemanTypeIs_opt_volatile( (v), double ) || \
    cavemanTypeIs_opt_volatile( (v), double *) || \
    cavemanTypeIs_opt_volatile( (v), double **) || \
    cavemanTypeIs_opt_volatile( (v), double ***) || \
    cavemanTypeIs_opt_volatile( (v), long double ) || \
    cavemanTypeIs_opt_volatile( (v), long double *) || \
    cavemanTypeIs_opt_volatile( (v), long double **) || \
    cavemanTypeIs_opt_volatile( (v), long double ***) || \
    cavemanTypeIs_opt_volatile( (v), void * ) ||\
    cavemanTypeIs_opt_volatile( (v), void ** ) || \
    cavemanTypeIs_opt_volatile( (v), void *** ) || \
    0 )

#define cavemanFormatPointer(value, localvalue, label, type, typelabel)	\
  if( cavemanTypeIs_opt_volatile( (value), type* ) )			\
    cavemanReturn = cavemanFormat("%s*(%u): %s = %0.*p", typelabel, (int)sizeof(localvalue), label, (int)(2*sizeof(localvalue)), *( type** ) &localvalue); \
  if( cavemanTypeIs_opt_volatile( (value), type** ) )			\
    cavemanReturn = cavemanFormat("%s**(%u): %s = %0.*p", typelabel, (int)sizeof(localvalue), label, (int)(2*sizeof(localvalue)), *( type*** ) &localvalue); \
  if( cavemanTypeIs_opt_volatile( (value), type*** ) )			\
    cavemanReturn = cavemanFormat("%s***(%u): %s = %0.*p", typelabel, (int)sizeof(localvalue), label, (int)(2*sizeof(localvalue)), *( type**** ) &localvalue)

#define cavemanFormatArray(value, localvalue, label, type, typelabel)	\
  if( cavemanTypeIs_opt_volatile( (value), type[] ) ) \
    cavemanReturn = cavemanFormat("%s(%u): %s = %0.*p", typelabel, (int)sizeof(localvalue), label, (int)(2*sizeof(type*)), *( type** ) &localvalue)

#define cavemanFormatCharPointer(value, localvalue, label, type, typelabel)	\
  cavemanFormatPointer(value, localvalue, label, type, typelabel);	\
  cavemanFormatPointer(value, localvalue, label, signed type, "s"typelabel);	\
  cavemanFormatPointer(value, localvalue, label, unsigned type, "u"typelabel); \
  cavemanFormatArray(value, localvalue, label, type, typelabel"[]");	\
  cavemanFormatArray(value, localvalue, label, signed type, "s"typelabel"[]");	\
  cavemanFormatArray(value, localvalue, label, unsigned type, "u"typelabel"[]")

#define cavemanFormatIntegerPointer(value, localvalue, label, type, typelabel)	cavemanFormatPointer(value, localvalue, label, type, typelabel)

#define cavemanFormatVoidPointer(value, localvalue, label, type, typelabel) cavemanFormatPointer((value), (localvalue), (label), type, (typelabel))
      
#define cavemanFormatInteger(value, localvalue, label, type, typelabel, fmtmod, decimalfmt) \
  if( cavemanTypeIs_opt_const( (value), type ) )			\
    cavemanReturn = cavemanFormat("%s(%u): %s = %" fmtmod decimalfmt " (0x%0.*" fmtmod "x)", typelabel, (int)sizeof(localvalue), label, *( type * ) &localvalue, (int)(2*sizeof(localvalue)), *( type * ) &localvalue)


#define cavemanFormatChar(value, localvalue, label, type, typelabel, fmtmod, decimalfmt) \
  if( cavemanTypeIs_opt_const( (value), type ) )			\
    cavemanReturn = cavemanFormat("%s(%u): %s = %" fmtmod decimalfmt " (0x%0.2" fmtmod "x, '%c')", typelabel, (int)sizeof(localvalue), label, *( type * ) &localvalue, *( type * ) &localvalue, * (type * ) &localvalue >= 0x20 && *(type * ) &localvalue <= 0x7e ? * (type * ) &localvalue : '?')

#define cavemanFormatReal(value, localvalue, label, type, typelabel, fmtmod, prec) \
  if( cavemanTypeIs_opt_volatile( (value), type ) )			\
    cavemanReturn = cavemanFormat("%s(%u): %s = %" fmtmod "g (%" "." #prec fmtmod "f)", typelabel, (int)sizeof(localvalue), label, *( type * ) &localvalue, *( type * ) &localvalue)


#define cavemanFormatSignedAndUnsignedInteger(value, localvalue, label, type, typelabel, fmtmod) \
  cavemanFormatInteger(value, localvalue, label, type, typelabel, fmtmod, "d");  \
  cavemanFormatInteger(value, localvalue, label, unsigned type, "u"typelabel, fmtmod, "u") 

#define cavemanFormatSignedAndUnsignedIntegerPointer(value, localvalue, label, type, typelabel) \
  cavemanFormatIntegerPointer(value, localvalue, label, signed type, typelabel);  \
  cavemanFormatIntegerPointer(value, localvalue, label, unsigned type, "u"typelabel); \
  cavemanFormatArray(value, localvalue, label, signed type, typelabel"[]");  \
  cavemanFormatArray(value, localvalue, label, unsigned type, "u"typelabel"[]") 

#define cavemanFormatSignedAndUnsignedIntegerAndPointer(value, localvalue, label, type, typelabel, fmtmod) \
  cavemanFormatSignedAndUnsignedInteger(value, localvalue, label, type, typelabel, fmtmod); \
  cavemanFormatSignedAndUnsignedIntegerPointer(value, localvalue, label, type, typelabel)

#define cavemanFormatRealAndPointer(value, localvalue, label, type, typelabel, fmtmod, prec) \
  cavemanFormatReal(value, localvalue, label, type, typelabel, fmtmod, prec); \
  cavemanFormatPointer(value, localvalue, label, type, typelabel)

#define cavemanFormatCTypes( v, __cm, label ) \
  cavemanFormatUserCTypes(v, __cm, label);			     \
  cavemanFormatChar((v), (__cm), label, char, "char", "hh", CAVEMAN_UNQUALIFIED_CHAR_FORMAT); /* char * != signed char * && != unsigned char * */ \
  cavemanFormatChar((v), (__cm), label, signed char, "schar", "hh", "u");		\
  cavemanFormatChar((v), (__cm), label, unsigned char, "uchar", "hh", "d");		\
  cavemanFormatCharPointer((v), (__cm), label, char, "char"); \
  cavemanFormatSignedAndUnsignedIntegerAndPointer((v), (__cm), label, int, "int", ""); \
  cavemanFormatSignedAndUnsignedIntegerAndPointer((v), (__cm), label, short, "short", "h"); \
  cavemanFormatSignedAndUnsignedIntegerAndPointer((v), (__cm), label, long, "long", "l"); \
  cavemanFormatSignedAndUnsignedIntegerAndPointer((v), (__cm), label, long long, "longlong", "ll"); \
  cavemanFormatRealAndPointer((v), (__cm), label, float, "float", "", __FLT_DIG__); \
  cavemanFormatRealAndPointer((v), (__cm), label, double, "double", "l", __DBL_DIG__); \
  cavemanFormatRealAndPointer((v), (__cm), label, long double, "longdouble", "L", __LDBL_DIG__); \
  cavemanFormatVoidPointer((v), (__cm), label, void, "void");


#define caveman(v) do { NSString *__msg = cavemanFormatValue((v),#v); \
    NSLog(@"%s:%d: %@", __PRETTY_FUNCTION__, __LINE__, __msg); [__msg release]; }while(0)
        
#define caveptr(v) do { void *__tmp = (void*) (v); NSString *__msg = cavemanFormatValue(__tmp,#v); \
        NSLog(@"%s:%d: %@", __PRETTY_FUNCTION__, __LINE__, __msg); [__msg release]; }while(0)

#define cavearray(v) do { void *__tmp = (void*) (v); NSString *__msg = cavemanFormatValue( ( __typeof__ (*v) *) __tmp, #v); \
        NSLog(@"%s:%d: %@", __PRETTY_FUNCTION__, __LINE__, __msg); [__msg release]; }while(0)

#if INTERNAL_WARNINGS
#warning cavestr is c-string only
#endif
#define cavestr(v) do { char *__msg = (v) ? cavemanFormat("cstring: %s = %p (%lu:\"%s\")", #v, (v), strlen(v), (v)) : \
      cavemanFormat("cstring: %s = %p (NULL)", #v, NULL);		\
    NSLog(@"%s:%d: %@", __PRETTY_FUNCTION__, __LINE__, __msg); [__msg release]; }while(0)        
        
#define caveint(v) do { int __tmp = (int) (v); NSString *__msg = cavemanFormatValue(__tmp,#v); \
    NSLog(@"%s:%d: %@", __PRETTY_FUNCTION__, __LINE__, __msg); [__msg release]; }while(0)        
        
#define caveobj(v) do { id __tmp = (id) (v); NSString *__msg = cavemanFormatValue(__tmp, #v); \
    NSLog(@"%s:%d: %@", __PRETTY_FUNCTION__, __LINE__, __msg); [__msg release]; }while(0)        

#define cavemanFormat(fmt, ...) [[NSString alloc] initWithFormat: @fmt, ## __VA_ARGS__]
//#define cavemanFormat(fmt, ...) CFStringCreateWithFormat(kCFAllocatorDefault, NULL /* fmtOptions */, CFSTR(fmt), ## __VA_ARGS__ )


#ifndef cavemanSupportedUserObjCType
#define cavemanSupportedUserObjCType(value) 0
#endif

#ifndef cavemanSupportedUserObjCTypes
#define cavemanFormatUserObjCTypes(value, localvalue, label) /**/
#endif

#define cavemanSupportedObjCType(v) ( \
				     cavemanSupportedUserObjCType(v) || \
				     cavemanTypeIs_opt_const((v),  NSRect ) || \
				     cavemanTypeIs_opt_const((v),  NSSize ) || \
				     cavemanTypeIs_opt_const((v),  NSPoint ) || \
				     cavemanTypeIs_opt_const((v),  NSRange ) || \
				     cavemanTypeIs_opt_const((v),  id ) || \
				     cavemanTypeIs_opt_const((v),  Class ) || \
				     cavemanTypeIs_opt_const((v),  SEL ) )

#define cavemanSupportedType(v) ( cavemanSupportedCType(v) || cavemanSupportedObjCType(v) )


#define cavemanFormatObjCTypes(v, __cm, label) \
  cavemanFormatUserCTypes(v, __cm, label);			     \
  if( cavemanTypeIs_opt_const((v),  NSRect ) )				\
    cavemanReturn = cavemanFormat("NSRect: %s = %@", label, NSStringFromRect(*(NSRect*)&__cm)); \
  if( cavemanTypeIs_opt_const((v),  NSSize ) )				\
    cavemanReturn = cavemanFormat("NSSize: %s = %@", label, NSStringFromSize(*(NSSize*)&__cm)); \
  if( cavemanTypeIs_opt_const((v),  NSPoint ) )				\
    cavemanReturn = cavemanFormat("NSPoint: %s = %@", label, NSStringFromPoint(*(NSPoint*)&__cm)); \
  if( cavemanTypeIs_opt_const((v),  NSRange ) )				\
    cavemanReturn = cavemanFormat("NSRange: %s = {%u%s, %u}", label,		\
			 (*(NSRange*) &__cm).location, (*(NSRange*) &__cm).location == NSNotFound ? " /* NSNotFound */" : "",(*(NSRange*) &__cm).length); \
  if( cavemanTypeIs_opt_const((v),  Class ) )				\
    cavemanReturn = cavemanFormat("class: %s = (%p) %s", label, *(Class *) &__cm, *(Class *)&__cm ? object_getClassName(*( Class *)&__cm) : "nil"); \
  if( cavemanTypeIs_opt_const((v),  SEL ) )				\
    cavemanReturn = cavemanFormat("SEL: %s = (%p) %s(%s)", label,		\
			 *(SEL *) &__cm, *(SEL *)&__cm ? "@selector" : "", *(SEL *)&__cm ? sel_getName(*(SEL *)&__cm) : "nil"); \
  if( cavemanTypeIs_opt_const((v),  id ) )				\
    cavemanReturn = cavemanFormat("id: %s = (%p) %@", label, *(id *) &__cm, *(id *) &__cm)


#define CAVEMAN_FORMAT_CHAR_S	0x1100 /*scH*/
#define CAVEMAN_FORMAT_CHAR_U	0x1101 /*ucH*/
#define CAVEMAN_FORMAT_CHAR_N	0x1102 /*ncH*/
#define CAVEMAN_FORMAT_INT_S	0x1200 /*si0*/
#define CAVEMAN_FORMAT_INT_U	0x1201 /*ui0*/
#define CAVEMAN_FORMAT_S_INT_S	0x1300 
#define CAVEMAN_FORMAT_S_INT_U  0x1301
#define CAVEMAN_FORMAT_L_INT_S  0x1400
#define CAVEMAN_FORMAT_L_INT_U  0x1401
#define CAVEMAN_FORMAT_LL_INT_S 0x1501
#define CAVEMAN_FORMAT_LL_INT_U 0x1501

#define CAVEMAN_FORMAT_FLOAT	0x2100
#define CAVEMAN_FORMAT_DOUBLE	0x2200
#define CAVEMAN_FORMAT_L_DOUBLE	0x2300

#define CAVEMAN_FORMAT_VOIDPTR  0x3100

#define CAVEMAN_FORMAT_ID       0x4100
#define CAVEMAN_FORMAT_CLASS    0x4200
#define CAVEMAN_FORMAT_SEL      0x4300

#define CAVEMAN_FORMAT_NSRANGE  0x8400

#define CAVEMAN_FORMAT_NSPOINT  0x8100
#define CAVEMAN_FORMAT_NSSIZE   0x8200
#define CAVEMAN_FORMAT_NSRECT   0x8300


#define CAVEMAN_FORMAT_CGPOINT  0x9100
#define CAVEMAN_FORMAT_CGSIZE   0x9200
#define CAVEMAN_FORMAT_CGRECT   0x9300


#define cavemanIs(v, what) (__builtin_types_compatible_p(__typeof__(v), what) )

#define cavemanIsObjC(v) (\
	cavemanIs( (v),  id ) ? CAVEMAN_FORMAT_ID : \
	cavemanIs( (v),  Class ) ? CAVEMAN_FORMAT_CLASS : \
	cavemanIs( (v),  SEL ) ? CAVEMAN_FORMAT_SEL : \
	0 )

#define cavemanIsFoundationStruct(v) (\
	cavemanIs( (v),  NSRange ) ? CAVEMAN_FORMAT_NSRANGE : \
	0 )

#define cavemanIsCGStruct(v) (\
	cavemanIs( (v),  CGPoint ) ? CAVEMAN_FORMAT_CGPOINT : \
	cavemanIs( (v),  CGSize ) ? CAVEMAN_FORMAT_CGSIZE : \
	cavemanIs( (v),  CGRect ) ? CAVEMAN_FORMAT_CGRECT : \
	0 )

#define cavemanIsCocoaStruct(v) (\
	cavemanIs( (v),  NSPoint ) ? CAVEMAN_FORMAT_NSPOINT : \
	cavemanIs( (v),  NSSize ) ? CAVEMAN_FORMAT_NSSIZE : \
	cavemanIs( (v),  NSRect ) ? CAVEMAN_FORMAT_NSRECT : \
	cavemanIsCGStruct(v) + cavemanIsFoundationStruct(v) )

#define cavemanIsIPhoneOSStruct(v) (\
	cavemanIsCGStruct(v) + cavemanIsFoundationStruct(v) )

#define cavemanIsBasicType(v) ( \
	cavemanIs( (v),  signed char ) ? CAVEMAN_FORMAT_CHAR_S : \
	cavemanIs( (v),  unsigned char ) ? CAVEMAN_FORMAT_CHAR_U : \
	cavemanIs( (v),  char ) ? CAVEMAN_FORMAT_CHAR_N : \
	cavemanIs( (v),  int ) ? CAVEMAN_FORMAT_INT_S : \
	cavemanIs( (v),  unsigned int ) ? CAVEMAN_FORMAT_INT_U : \
	cavemanIs( (v),  short ) ? CAVEMAN_FORMAT_S_INT_S : \
	cavemanIs( (v),  unsigned short ) ? CAVEMAN_FORMAT_S_INT_U : \
	cavemanIs( (v),  long int ) ? CAVEMAN_FORMAT_L_INT_S : \
	cavemanIs( (v),  unsigned long ) ? CAVEMAN_FORMAT_L_INT_U : \
	cavemanIs( (v),  long long ) ? CAVEMAN_FORMAT_LL_INT_S : \
	cavemanIs( (v),  unsigned long long ) ? CAVEMAN_FORMAT_LL_INT_U : \
	cavemanIs( (v),  float ) ? CAVEMAN_FORMAT_FLOAT : \
	cavemanIs( (v),  double ) ? CAVEMAN_FORMAT_DOUBLE : \
	cavemanIs( (v),  long double ) ? CAVEMAN_FORMAT_L_DOUBLE : \
	0 )

#define cavemanIsVoidPtr(v) ( \
	( cavemanIs( (v),  void * ) || cavemanIs( (v),  const void * ) ) ? CAVEMAN_FORMAT_VOIDPTR : \
	0 )

#if __OBJC__
#define cavemanIsLanguageType(v) ( cavemanIsBasicType(v) + cavemanIsVoidPtr(v) + cavemanIsObjC(v) ) 
#else
#define cavemanIsLanguageType(v) ( cavemanIsBasicType(v) + cavemanIsVoidPtr(v) ) 
#endif

#if TARGET_OS_IPHONE
#define cavemanIsKnownType(v) (cavemanIsLanguageType(v) + cavemanIsIPhoneOSStruct(v) )
#else 
#define cavemanIsKnownType(v) (cavemanIsLanguageType(v) + cavemanIsCocoaStruct(v) )
#endif


#define autoFormat(v, label) ({ \
	struct __cmBadType { int dummy; } __cmBadType = { 0 }; /* used to generate a halfway decent error message at compile time */ \
	__typeof__ (v) __cmv = (v) ; \
	void *cavemanReturn = __builtin_choose_expr( cavemanIsKnownType( v ), (void *) 0, __cmBadType ); \
	if( NULL != cavemanReturn ) { fprintf(stderr, "CAVEMAN: THIS PATH SHOULD BE PREVENTED BY THE COMPILER\n"); abort(); } \
	int __cmType = cavemanIsKnownType( __cmv ); \
	NSLog(@"auto: %s %04x size %d enc: %s", label, __cmType, sizeof(__cmv), @encode( __typeof__ (__cmv) )); \
	cavemanReturn; \
}) 

#define TESTobjCFormat(v, label) ({ \
	__typeof__ (v) __cmv = (v) ; \
	char *type = __builtin_types_compatible_p( __typeof__(__cmv), long double) ? "D" : @encode( __typeof__ (__cmv) ); \
	NSValue *__cmnsv = [[NSValue alloc] initWithBytes: &__cmv objCType: type]; /* NSValue secretly supports 'D'... */ \
	id __cmfmt = formatType(type, (void*)&__cmv); \
	NSLog(@"auto: %s size %d enc: %s v: %@ vt: %s f: %@", label, (int)sizeof(__cmv), type, __cmnsv, [__cmnsv objCType], __cmfmt); \
	[__cmnsv release]; \
	/* [__cmfmt release]; */ \
}) 

#define formatObjCValue(v, label) ({ \
	__typeof__ (v) __cmv = (v) ; \
	char *type = __builtin_types_compatible_p( __typeof__(__cmv), long double) ? "D" : @encode( __typeof__ (__cmv) ); \
	NSString *__cmfmt = formatType(type, (void*)&__cmv); \
	__cmfmt = [[label stringByAppendingString: @":"] stringByAppendingString: __cmfmt]; \
	__cmfmt; \
}) 



#define F(v) formatObjCValue(v, #v)

// read: http://developer.apple.com/documentation/Cocoa/Conceptual/GarbageCollection/Articles/gcCoreFoundation.html
// also: http://www.cocoabuilder.com/archive/message/cocoa/2008/8/7/215098
#define AUTORELEASE_CF(cf) ( (NULL == (cf)) ? (__typeof__((cf))) NULL : (__typeof__((cf))) [(id) CFMakeCollectable(cf) autorelease] )
#define AUTORELEASE_CF_AS_ID(cf) ( (NULL == (cf)) ? nil : [(id) CFMakeCollectable( (CFTypeRef) cf) autorelease] )
#define RETAIN_CF(cf) ( (NULL == (cf)) ? (__typeof__((cf))) NULL : (__typeof__((cf))) [(id) CFMakeCollectable(cf) retain] )



id formatType(const char *type, void *data) 
{
	if( NULL == type ) 
		return @"NILTYPE";

	id ret = nil;

	if('r' == *type) {
		++type;
	}

	void *ptr = *(void **) data;
		
	
	switch( *type ) {
		case '@':
		case '#':
			ret = [(id) ptr description]; break;

		case '*': ret = [NSString stringWithFormat: @"char*: '%s'", *(char **)data]; break;

		case 'c': ret = [NSString stringWithFormat: @"char: 0x%02hhx", *(char *)data]; break;
		case 'C': ret = [NSString stringWithFormat: @"uchar: 0x%02hhx", *(unsigned char *)data]; break;
		case 's': ret = [NSString stringWithFormat: @"short: 0x%02hx", *(short *)data]; break;
		case 'S': ret = [NSString stringWithFormat: @"ushort: 0x%02hx", *(unsigned short *)data]; break;
		case 'i': ret = [NSString stringWithFormat: @"int: 0x%02x", *(int *)data]; break;
		case 'I': ret = [NSString stringWithFormat: @"uint: 0x%02x", *(unsigned int *)data]; break;
		case 'l': ret = [NSString stringWithFormat: @"long: 0x%02lx", *(long *)data]; break;
		case 'L': ret = [NSString stringWithFormat: @"ulong: 0x%02lx", *(unsigned long *)data]; break;
		case 'q': ret = [NSString stringWithFormat: @"quad: 0x%02llx", *(long long *)data]; break;
		case 'Q': ret = [NSString stringWithFormat: @"uquad: 0x%02llx", *(unsigned long long *)data]; break;
		case 'f': ret = [NSString stringWithFormat: @"float: %.*g", __FLT_DIG__, *(float *)data]; break;
		case 'd': ret = [NSString stringWithFormat: @"double: %.*lg", __DBL_DIG__, *(double *)data]; break;

		/* warning: not officially supported - not generated by @encode but works in NSValue */
		case 'D': ret = [NSString stringWithFormat: @"double: %.*Lg", __LDBL_DIG__, *(long double *)data]; break;

		case ':': ret = NSStringFromSelector(*(SEL*)data); break;

		case '{': 
			if( 0 == strncmp(type+1, "_NSRange=", 9) ) {
				ret = NSStringFromRange( *(NSRange *) data);
			} else if( 0 == strncmp(type+1, "_NSPoint=", 9) ) {
				ret = NSStringFromPoint( *(NSPoint *) data);
			} else if( 0 == strncmp(type+1, "_NSSize=", 8) ) {
				ret = NSStringFromSize( *(NSSize *) data);
			} else if( 0 == strncmp(type+1, "_NSRect=", 8) ) {
				ret = NSStringFromRect( *(NSRect *) data);
			} else if( 0 == strncmp(type+1, "CGPoint=", 8) ) {
				ret = NSStringFromPoint( *(NSPoint *) data);
			} else if( 0 == strncmp(type+1, "CGSize=", 7) ) {
				ret = NSStringFromSize( *(NSSize *) data);
			} else if( 0 == strncmp(type+1, "CGRect=", 7) ) {
				ret = NSStringFromRect( *(NSRect *) data);
			} else {
				ret = [NSString stringWithFormat: @"struct(%s)", type]; break;
			}
			break;


		case '[': ret = [NSString stringWithFormat: @"array(%s)", type]; break;

		case '^': 

			if( 0 == strncmp(type+1, "{__CF", 5)) {
				if(	0 == strncmp(type+6, "String=", 7) || 0 == strncmp(type+6, "Number=", 7) ) {
					ret = [(id) ptr description];
				} else {
#warning MakeCollectable				
					ret = AUTORELEASE_CF_AS_ID( CFCopyDescription( (CFTypeRef) ptr) );			
				}
			} else {
				switch( type[1] ) {
				
					case '{': ret = [NSString stringWithFormat: @"struct*(%s): %p", type, ptr]; break;
					case '?': ret = [NSString stringWithFormat: @"func*: %p", ptr]; break;
					case '^': ret = [NSString stringWithFormat: @"ptr*: %p", ptr]; break;
					case '*': ret = [NSString stringWithFormat: @"char**: %p", ptr]; break;
					case 'v': ret = [NSString stringWithFormat: @"void*: %p", ptr]; break;

					case 'B': 
					case 'c': 
					case 'C': 
					case 's': 
					case 'S': 
					case 'i': 
					case 'I': 
					case 'l': 
					case 'L': 
					case 'q': 
					case 'Q': 
					case 'f': 
					case 'd': 
					case 'D': /* won't be seen - no special case code - so it is ^d */
					case '@': 
					case '#': 
					case ':': 
						ret = [NSString stringWithFormat: @"basic(%c)*: %p", type[1], ptr]; break;

					default:
						ret = [NSString stringWithFormat: @"other(%c)*: %p", type[1], ptr]; break;
				}
			}
			break;

		case 'B': ret = @"C++ Bool or C99 _Bool - still unsupported"; break;
		case 'b': ret = @"bitfield - still unsupported"; break;

		case '?': ret = @"unknown type (?)"; break;
		
		default:
			ret = [NSString stringWithFormat: @"unknown type character '%c'", *type];
			break;
	}
		
	return ret ? ret : [NSString stringWithFormat: @"type not decoded (%s)", type];

}

void test(char carray[])
{
	F(carray);
}

int main (int argc, const char * argv[]) {
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

	BOOL _bool;
	F(_bool = NO);

	
	char _char;
	signed char _signed_char;
	unsigned char _unsigned_char;

	F(_char = 1);
	F(_signed_char = -128);
	F(_unsigned_char = 255);

	signed short _signed_short;
	unsigned short _unsigned_short;

	F(_signed_short = -32768);
	F(_unsigned_short = 65535);

	int _int;
	unsigned int _unsigned_int;

	F(_int = -32769);
	F(_unsigned_int = 65536);
	
	long _long;
	unsigned long _unsigned_long;

	F(_long = -(1<<16));
	F(_unsigned_long = 1<<16);

	long long _long_long;
	unsigned long long _unsigned_long_long;

	F(_long_long = -(1LL<<32));
	F(_unsigned_long_long = 1LL<<32);

	float _float;
	double _double;
	long double _long_double;
	
	F(_float = __FLT_MIN__);
	F(_float = __FLT_MAX__);
	F(&_float);
	F(_double = __DBL_MIN__);
	F(_double = __DBL_MAX__);
	F(&_double);

	F(_long_double = __LDBL_MIN__);
	F(_long_double = __LDBL_MAX__);
	F(&_long_double);

	void *_void_ptr;
	const void *_const_void_ptr;

	F( _void_ptr = main );
	F( _const_void_ptr = _void_ptr );

	int (*_func_ptr)(int argc, const char **argv);

	F( _func_ptr = main );

	NSRange _nsrange;

	F(_nsrange = NSMakeRange(1,2));

	NSInteger _nsinteger;
	NSUInteger _nsuinteger;

	F(_nsinteger = -(1<<16));
	F(_nsuinteger = 1<<16);

	CGFloat _cgfloat;

	F(_cgfloat = 1e-6);

	CGPoint _cgpoint;
	CGSize _cgsize;
	CGRect _cgrect;

	F(_cgpoint = CGPointMake(1.1, 2.2));
	F(_cgsize = CGSizeMake(3.3, 4.4));
	F(_cgrect = CGRectMake(5.5, 6.6, 7.7, 8.8));

	NSPoint _nspoint;
	NSSize _nssize;
	NSRect _nsrect;

	F(_nspoint = NSMakePoint(1.1, 2.2));
	F(_nssize = NSMakeSize(3.3, 4.4));
	F(_nsrect = NSMakeRect(5.5, 6.6, 7.7, 8.8) );

	id _id;
	Class _class;
	SEL _sel;
	
	F( _id = [NSString stringWithString: @"an id"] );
	F( _class = [_id class] );
	F( _sel = @selector(stringWithString:) );

	CFStringRef _cfstringref;
	NSString *_nsstring_ptr;
	NSString **_nsstring_ptr_ptr;
	
	_cfstringref = CFSTR("CF String");
	
	F(_cfstringref);
	F(_nsstring_ptr = @"NS String");
	F(_nsstring_ptr_ptr = &_nsstring_ptr);

	F(CFSTR("Constant CF String"));
	F(@"Constant NS String");

	F("Literal C String");
	F(argv);
	F(argv[0]);
	F(argv[0][0]);
	
	int iback[] = {1,2,3};
	int *iarray = iback;
	
	char cback[] = {33,34,35};
	
//	F(cback);
//	F(iback);

	test(cback);
	char *cptr = "Constant C String";
	
	F(cptr);



	CFCalendarRef _calendarRef = CFCalendarCopyCurrent();
	F(_calendarRef);
	CFRelease(_calendarRef);

    [pool drain];
    return 0;
}

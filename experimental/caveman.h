/*
 This file is part of EngineRoom, Copyright (c) 2007-2010 Bjoern Kriews, Hamburg - All rights reserved.

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

#ifndef __CAVEMAN_H__
#define __CAVEMAN_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <sys/time.h>

#ifdef __sun
#include "er_util.h"
#define caveman_asprintf util_asprintf
#else
#define caveman_asprintf asprintf
#endif

#if __CHAR_UNSIGNED__
#define CAVEMAN_UNQUALIFIED_CHAR unsigned char
#define CAVEMAN_UNQUALIFIED_CHAR_FORMAT "u"
#else
#define CAVEMAN_UNQUALIFIED_CHAR signed char
#define CAVEMAN_UNQUALIFIED_CHAR_FORMAT "d"
#endif

#ifdef NO_DEBUG
#define caveman(x)  /**/
#define caveptr(x)  /**/
#define caveobj(x)  /**/
#define caveint(x)  /**/

#else

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
    if( ! cavemanSupportedType( v ) )  { \
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

#ifdef __OBJC__
#import <Foundation/Foundation.h>

#define caveman(v) do { NSString *__msg = cavemanFormatValue((v),#v); \
    NSLog(@"%s:%d: %@", __PRETTY_FUNCTION__, __LINE__, __msg); [__msg release]; }while(0)
        
#define caveptr(v) do { void *__tmp = (void*) (v); NSString *__msg = cavemanFormatValue(__tmp,#v); \
        NSLog(@"%s:%d: %@", __PRETTY_FUNCTION__, __LINE__, __msg); [__msg release]; }while(0)

#define cavearray(v) do { void *__tmp = (void*) (v); NSString *__msg = cavemanFormatValue( ( __typeof__ (*v) *) __tmp, #v); \
        NSLog(@"%s:%d: %@", __PRETTY_FUNCTION__, __LINE__, __msg); [__msg release]; }while(0)

#if MAINTAINER_WARNINGS
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

#else

#define caveman(v) do { char *__msg = cavemanFormatValue((v),#v); \
    fprintf(stderr, "%s:%d: %s\n", __PRETTY_FUNCTION__, __LINE__, __msg); free(__msg); }while(0)

#define caveptr(v) do { void *__tmp = (void*) (v); char *__msg = cavemanFormatValue(__tmp, #v); \
        fprintf(stderr, "%s:%d: %s\n", __PRETTY_FUNCTION__, __LINE__, __msg); free(__msg); }while(0)

#define cavearray(v) do { void *__tmp = (void*) (v); char *__msg = cavemanFormatValue( ( __typeof__ (*v) *) __tmp, #v); \
        fprintf(stderr, "%s:%d: %s\n", __PRETTY_FUNCTION__, __LINE__, __msg); free(__msg); }while(0)

#define cavestr(v) do { char *__msg = (v) ? cavemanFormat("cstring: %s = (%p) (%lu:\"%s\")", #v, (v), strlen(v), (v)) :  \
      cavemanFormat("cstring: %s = %p (NULL)", #v, NULL);		\
        fprintf(stderr, "%s:%d: %s\n", __PRETTY_FUNCTION__, __LINE__, __msg); free(__msg); }while(0)

#define caveint(v) do { int __tmp = (int) (v); char *__msg = cavemanFormatValue(__tmp, #v); \
        fprintf(stderr, "%s:%d: %s\n", __PRETTY_FUNCTION__, __LINE__, __msg); free(__msg); }while(0)        

#define cavemanFormat(fmt, ...) ({ char *__frv; caveman_asprintf(&__frv, fmt, ## __VA_ARGS__); __frv; })

#define cavemanSupportedType(v) (cavemanSupportedCType(v))
#define cavemanFormatObjCTypes(func,v,label) /**/

#endif
/* __OBJC__ */

#endif
/* NO_DEBUG */

#endif
/* __CAVEMAN_H__ */

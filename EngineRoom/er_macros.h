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

#ifndef __ER_MACROS_H__
#define __ER_MACROS_H__

#define _ER_VERSION      1.1.17r0
#define _ER_VERSION_HEX 0x0111700 
/* Apples CFBundleVersion has arcane restrictions 
 Bundle: MMmf.fr.r Hex: 0xMMmffrr MAJORMAJOR.minor.fixfixreleaserelease 
*/

#ifndef ER_VERSION
#define ER_VERSION		_ER_VERSION
#define ER_VERSION_HEX  _ER_VERSION_HEX
#else
#if _ER_VERSION_HEX != ER_VERSION_HEX
#error EngineRoom: Version number in er_macros.h does not match external definition
#endif
#endif

/*
 * expands to the number of arguments (up to 20) it was given
 * returns 1 for 1 AND zero arguments, see ER_COUNT_ARGS_PLUS1 for a solution
 * credit for the technique goes to Steven Fuerst 
 * http://locklessinc.com/articles/overloading/ 
 */
#define ER_COUNT_NONZERO_ARGS(...) _ER_COUNT_NONZERO_ARGS_HELPER(__VA_ARGS__, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define _ER_COUNT_NONZERO_ARGS_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _, ...) _

/* expands to the number of arguments plus 1 - and works for the no argument case */
#define ER_COUNT_ARGS_PLUS1(...) ER_COUNT_NONZERO_ARGS(dummy, ## __VA_ARGS__)

/* helper macro to convert preprocessor symbols into strings */
#define _ER_STRINGIFY(s) #s
#define ER_STRINGIFY(s) _ER_STRINGIFY(s)

/* helper macro to combine tokens */
#define ER_CAT(A, B) _ER_CAT_HELPER(A, B)
#define _ER_CAT_HELPER(A, B) A ## B

/* 
 * #define something ER_VARARGS_TO_ONELESSTHAN(something, ## __VA_ARGS__)
 * transforms:
 * something()      -> somethingOneLessThan1()
 * something(x)     -> somethingOneLessThan2(x)
 * something(x,y)   -> somethingOneLessThan3(x,y) 
 * something(x,y,z) -> somethingOneLessThan4(x,y,z) 
 *
 * which is useful if you need to inspect or stringify arguments
 */
#define ER_VARARGS_TO_NONZERO_ARGS(prefix, ...) ER_CAT( prefix, ER_COUNT_NONZERO_ARGS(__VA_ARGS__))(__VA_ARGS__)
#define ER_VARARGS_TO_ONELESSTHAN(prefix, ...) ER_CAT( ER_CAT(prefix, OneLessThan), ER_COUNT_ARGS_PLUS1(__VA_ARGS__))(__VA_ARGS__)

#endif
/* __ER_MACROS_H__ */

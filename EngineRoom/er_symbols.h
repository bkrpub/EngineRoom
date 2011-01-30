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

#ifndef __ER_SYMBOLS_H__
#define __ER_SYMBOLS_H__

// work in progress
#define ER_SYMBOL_VISIBLE			/* __attribute__((visibility("default"))) */
#define ER_SYMBOL_VISIBLE_EMBEDDED	/* __attribute__((visibility("default"))) */
#define ER_SYMBOL_HIDDEN			/* __attribute__((visibility("hidden"))) */
#define ER_SYMBOL_WEAK_IMPORT		__attribute__((weak_import))

#if MAINTAINER_WARNINGS
#warning BK: match up with unused from er_util
#endif
#define ER_SYMBOL_USED					/* __attribute__((visibility("used"))) */


#ifdef ER_EMBEDDED_NAME

#define ER_EMBEDDED_NAME_AS_STRING ER_STRINGIFY(ER_EMBEDDED_NAME)

#define ER_SYMBOL_EMBEDDED_NAME(symbolName) ER_CAT( ER_CAT(ER_EMBEDDED_NAME, _), symbolName)

#if ER_EMBEDDED_IGNORE_GLOBAL
#define ER_ADDRESS_OF_GLOBAL_OR_EMBEDDED(symbolName) ( &ER_SYMBOL_EMBEDDED_NAME(symbolName) )
#else
#define ER_ADDRESS_OF_GLOBAL_OR_EMBEDDED(symbolName) ( NULL == &symbolName ? &ER_SYMBOL_EMBEDDED_NAME(symbolName) : &symbolName )
#endif

#else
/* ! ER_EMBEDDED_NAME */

#define ER_EMBEDDED_NAME_AS_STRING ""

#define ER_SYMBOL_EMBEDDED_NAME(symbolName) symbolName

#define ER_ADDRESS_OF_GLOBAL_OR_EMBEDDED(symbolName) (&symbolName)

#endif
/* ER_EMBEDDED_NAME */

#endif
/* __ER_SYMBOLS_H__ */

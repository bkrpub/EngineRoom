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

// used internally for now, may be exported later, can not simply be compiled for 32 and 64

#ifndef __ER_COMPAT_H__
#define __ER_COMPAT_H__ 1

#ifdef __APPLE__

#import <AvailabilityMacros.h>

#ifdef __OBJC__

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

#if MAC_OS_X_VERSION_MIN_REQUIRED >= 1050
#define COMPAT_OBJECT_GETCLASS(cls) object_getClass(cls)
#define COMPAT_CLASS_GETNAME(cls) class_getName(cls)
#define COMPAT_METHOD_GETNAME(m) method_getName(m)
#define COMPAT_METHOD_GETIMPLEMENTATION(m) method_getImplementation(m)
#define COMPAT_CLASS_ISMETACLASS(cls) class_isMetaClass( cls )
#define COMPAT_CLASS_COPYMETHODLIST(cls, countPtr) class_copyMethodList( (cls), (countPtr) )
#else
/* wrappers for weak references to 2.0 objc runtime functions or substitutes */
#define COMPAT_OBJECT_GETCLASS(cls) ( object_getClass ? object_getClass(cls) : (cls)->isa )
#define COMPAT_CLASS_GETNAME(cls) ( class_getName ? class_getName(cls) : (cls)->isa->name )		  
#define COMPAT_METHOD_GETNAME(m) ( method_getName ? method_getName(m) : (m)->method_name )		  
#define COMPAT_METHOD_GETIMPLEMENTATION(m) ( method_getName ? method_getImplementation(m) : (m)->method_imp )		  
#define COMPAT_CLASS_ISMETACLASS(cls) ( class_isMetaClass ? class_isMetaClass( cls ) : ( cls->info & CLS_META ? YES : NO ) )
#define COMPAT_CLASS_COPYMETHODLIST(cls, countPtr) ( (class_copyMethodList ? class_copyMethodList : class_copyMethodList_emulation)( (cls), (countPtr) ) )
#endif

#endif
/* __OBJC__ */

#endif
/* __APPLE__ */


#endif
/* __ER_COMPAT_H__ */

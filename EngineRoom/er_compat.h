/*
 * used internally for now, may be exported later, can not simply be compiled for 32 and 64
 */

#ifndef __ER_COMPAT_H__
#define __ER_COMPAT_H__ 1

#ifdef __APPLE__

#import <AvailabilityMacros.h>

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
/* __APPLE__ */


#endif
/* __ER_COMPAT_H__ */

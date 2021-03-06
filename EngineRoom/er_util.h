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

#ifndef __ER_UTIL_H__
#define __ER_UTIL_H__

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <alloca.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <pthread.h>

#include <time.h>
#include <sys/time.h>

#include <stddef.h>

#if defined(__linux__)
/* needed for link.h (dl_iterate_phdr) and vasprintf on linux */
#define _GNU_SOURCE /* as documented */
#define __USE_GNU /* as needed by vasprintf */
#include <link.h>
#endif

#if defined(__linux__) || defined(__APPLE__) 
#include <execinfo.h>
#endif

#ifdef ER_CONFIG_FILE
#include ER_CONFIG_FILE
#endif

#define UTIL_EMPTY ({ })

#if defined(__GNUC__) || defined(__sun)
#define UTIL_UNUSED __attribute__((unused))
#else
#define UTIL_UNUSED /* unused variable */
#endif

#ifdef __GNUC__
#define UTIL_NO_INSTRUMENT __attribute__((__no_instrument_function__))
#else
#define UTIL_NO_INSTRUMENT /**/
#endif

/* osf is completely unsupported, linux alpha untested, this is just a "well known" list */
#if defined(__LP64__) || defined(__powerpc64__) || defined(__osf__) || defined(__64BIT__) || defined(_LP64)
#define UTIL_64BIT 1
#define UTIL_INVALID_POINTER ((void*)0xFFFFFFFFFFFFFFFFLL)
#else
#define UTIL_INVALID_POINTER ((void*)0xFFFFFFFF)
#endif

#define UTIL_PTR_AS_ULL(p) ((unsigned long long)(uintptr_t)(p))


#define __UTIL_FUNCTION__        __func__
#ifdef __GNUC__
#define __UTIL_PRETTY_FUNCTION__ __PRETTY_FUNCTION__
#else
#define __UTIL_PRETTY_FUNCTION__ __func__
#endif

#define UTIL_PATH_SEPARATOR '/'


#define utilMessage(fmt, ...) fprintf(stderr, "%s: " fmt "\n", __PRETTY_FUNCTION__, ## __VA_ARGS__ )
#define utilReturnWithMessage(ret, fmt, ...) do{ utilMessage("ERROR " fmt, ## __VA_ARGS__ ); return ret; }while(0)

#define utilDebugIf(enable, fmt, ...) do{ if( enable ) utilMessage(#enable " " fmt,  ## __VA_ARGS__ ); }while(0)
#define utilDebug(enable, fmt, ...) do{ utilMessage(fmt, ## __VA_ARGS__ ); }while(0)


#ifdef __APPLE__

#include <mach-o/loader.h>

#ifdef UTIL_64BIT
#define UTIL_MACH_HEADER const struct mach_header_64
#define UTIL_SEGMENT_COMMAND struct segment_command_64
#define UTIL_NLIST const struct nlist_64
#else
#define UTIL_MACH_HEADER const struct mach_header
#define UTIL_SEGMENT_COMMAND struct segment_command
#define UTIL_NLIST const struct nlist
#endif

#endif
/* __APPLE__ */

#if __OBJC__

/*
 * macros to retain and autorelease CoreFoundation objects correctly with and without GC
 */

// read: http://developer.apple.com/documentation/Cocoa/Conceptual/GarbageCollection/Articles/gcCoreFoundation.html
// also: http://www.cocoabuilder.com/archive/message/cocoa/2008/8/7/215098


#define UTIL_AUTORELEASE_CF_AS_ID(cf) ({ CFTypeRef __utilARcf = (CFTypeRef) (cf); __utilARcf ? [(id) CFMakeCollectable( __utilARcf ) autorelease] : nil; })

// I am still not entirely sure if this is right:
#define UTIL_RETAIN_CF(cf) ({ CFTypeRef __utilRTcf = (CFTypeRef) (cf); __utilRTcf ? ( __typeof__((cf)) ) [(id) CFMakeCollectable( __utilRTcf ) retain] : NULL; })

#define UTIL_AUTORELEASE_CF(cf) ( ( __typeof__((cf)) ) UTIL_AUTORELEASE_CF_AS_ID(cf) )

#define ER_AUTORELEASE_CF(cf)       UTIL_AUTORELEASE_CF(cf)
#define ER_AUTORELEASE_CF_AS_ID(cf) UTIL_AUTORELEASE_CF_AS_ID(cf)
#define ER_RETAIN_CF(cf)            UTIL_RETAIN_CF(cf)

#endif


#define util_watch_start(name) struct timeval name##_util_watch; gettimeofday(&name##_util_watch, NULL);
#define util_watch_seconds(name) ({ util_watch_start(name##_read); \
      (name##_read_util_watch.tv_sec + 1e-6 * name##_read_util_watch.tv_usec) - (name##_util_watch.tv_sec + 1e-6 * name##_util_watch.tv_usec); })


void *util_map_image(const char *file, size_t *lengthPtr);
void util_unmap_image(void *image, size_t length);

int util_asprintf(char **ret, const char *fmt, ...);
int util_vasprintf(char **ret, const char *fmt, va_list ap);

/* prepends cross-timezone-sortable timestamp, human readable timestamp, pid */
int util_log_asprintf(char **ret, const char *fmt, ...);
int util_log_vasprintf(char **ret, const char *fmt, va_list ap);

#endif
/* __ER_UTIL_H__ */

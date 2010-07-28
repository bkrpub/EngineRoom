/*
 *  $Id: logpoints_types.h 721 2008-03-14 00:18:42Z bkr $
 *
 *  Copyright (c) 2007 Bjoern Kriews
 */

#ifndef __LOGPOINTS_TYPES_H__
#define __LOGPOINTS_TYPES_H__ 1

#include "er_util.h"

#import <sys/types.h>
#import <inttypes.h>

#if __LOGPOINTS_C__
#define LOGPOINT_EXTERN_C(name, type, value) type name = value
#else
#define LOGPOINT_EXTERN_C(name, type, value) extern type name
#endif

#ifdef UTIL_64BIT
typedef uint64_t lp_uint_t;
typedef int64_t lp_int_t;
#define LOGPOINT_EXPECTED_SIZE  128
#else
typedef uint32_t lp_uint_t;
typedef int32_t lp_int_t;
#define LOGPOINT_EXPECTED_SIZE  64
#endif

typedef lp_int_t lp_return_t;

typedef struct logpoint {
    lp_uint_t magic;
    lp_uint_t size;
    const char *kind;
    const char *keys;
    const char *function;
    const char *file;
    lp_uint_t line;
    lp_uint_t flags;
    lp_int_t count; /* -1: not counted */
    const char *image; /* set by logpoint loader  */
    void *address;
    const char *label;

    char *formatInfo; /* stringified version of format string and arguments */

    struct logpoint *next; /* set by logpoint loader (unused, experimental) */

    lp_uint_t reserved1;

    lp_uint_t magic2;
    /* 14 * 4 = 40 bytes on 32bit, padded to 64 because this happens on i386 anyway, 128 on 64bit */
} LOGPOINT;

#define LOGPOINT_MAGIC 0x40343240
#define LOGPOINT_MAGIC2(line) ( LOGPOINT_MAGIC - (line) - 63490 * sizeof(LOGPOINT))

#define LOGPOINT_MAGIC_TEST(lp) (LOGPOINT_MAGIC == (lp).magic && LOGPOINT_EXPECTED_SIZE == (lp).size && LOGPOINT_MAGIC2((lp).line) == (lp).magic2 )

/* logpoint flags */
#define LOGPOINT_NOFLAGS                    0           /* for readability */

#define LOGPOINT_PRIORITIZED                (1 << 31)   /* message has a syslog-compatible priority in bits 30-28 */
#define LOGPOINT_IS_PRIORITIZED(lp)         LOGPOINT_FLAG((lp), LOGPOINT_PRIORITIZED)

#define LOGPOINT_PRIORITY_MASK              (7 << 28)
#define LOGPOINT_PRIORITY(lp)               ( ( (lp).flags << 28 ) & 7 )

#define LOGPOINT_DEBUG                      (7 << 28)   
#define LOGPOINT_INFO                       (6 << 28)   
#define LOGPOINT_NOTICE                     (5 << 28)   
#define LOGPOINT_WARNING                    (4 << 28)   
#define LOGPOINT_ERROR                      (3 << 28)   
#define LOGPOINT_CRITICAL                   (2 << 28)   
#define LOGPOINT_ALERT                      (1 << 28)   
#define LOGPOINT_EMERGENCY                  (0 << 28)   

#define LOGPOINT_CXX                        (1 << 27)    /* langspec data is for C++ (this, NULL) */
#define LOGPOINT_OBJC                       (1 << 26)    /* langspec data is for ObjC (self, _cmd) */
#define LOGPOINT_C                          (1 << 25)    /* langspec data is for C (NULL, NULL) */

#define LOGPOINT_LANGUAGE_MASK              ( LOGPOINT_C | LOGPOINT_OBJC | LOGPOINT_CXX )
#define LOGPOINT_LANGUAGE(lp)               ( (lp).flags & LOGPOINT_LANGUAGE_MASK )                      

#define LOGPOINT_IS_CXX(lp)                 LOGPOINT_FLAG((lp), LOGPOINT_CXX)
#define LOGPOINT_IS_OBJC(lp)                LOGPOINT_FLAG((lp), LOGPOINT_OBJC)
#define LOGPOINT_IS_C(lp)                   LOGPOINT_FLAG((lp), LOGPOINT_C)

#define LOGPOINT_NOTE                       (1 << 10)   /* logpoint is used for developer notes */
#define LOGPOINT_TRACE                      (1 << 9)    /* logpoint is used for tracer messages */
#define LOGPOINT_SWITCH                     (1 << 8)    /* logpoint is used to conditionally enable other code */
#define LOGPOINT_ASSERT                     (1 << 7)    /* handled as an assertion according to environment  */
#define LOGPOINT_NSSTRING                   (1 << 6)    /* user strings stored in the logpoint are nsstring instances (work in progress, ObjC only) */
#define LOGPOINT_BACKTRACE                  (1 << 5)    /* logpoint should obtain a stacktrace */
#define LOGPOINT_SILENT                     (1 << 4)    /* does not emit log message - used for switches */
#define LOGPOINT_BROKEN                     (1 << 3)    /* used by clients (experimental, i.e. caveman.h) */
#define LOGPOINT_DYNAMIC_CODE               (1 << 2)    /* is in dynamically linked code */
#define LOGPOINT_HARD                       (1 << 1)    /* unconditional, not affected by default filtering */
#define LOGPOINT_ACTIVE                     (1 << 0)    /* does logpoint currently log ?  */


#define LOGPOINT_FLAG(lp,bitValue)          (((lp).flags & (bitValue)) ? 1 : 0)
#define LOGPOINT_SET_FLAG(lp,bitValue,flag) (lp.flags = ( ( lp.flags & ~(bitValue) ) | ( flag ? (bitValue) : 0 ) ) ) 

/* incomplete */
#define LOGPOINT_IS_NOTE(lp)                LOGPOINT_FLAG((lp), LOGPOINT_NOTE)
#define LOGPOINT_IS_TRACE(lp)               LOGPOINT_FLAG((lp), LOGPOINT_TRACE)
#define LOGPOINT_IS_SWITCH(lp)              LOGPOINT_FLAG((lp), LOGPOINT_SWITCH)
#define LOGPOINT_IS_ASSERT(lp)              LOGPOINT_FLAG((lp), LOGPOINT_ASSERT)
#define LOGPOINT_IS_NSSTRING(lp)            LOGPOINT_FLAG((lp), LOGPOINT_NSSTRING)
#define LOGPOINT_IS_BACKTRACE(lp)           LOGPOINT_FLAG((lp), LOGPOINT_BACKTRACE)
#define LOGPOINT_IS_SILENT(lp)              LOGPOINT_FLAG((lp), LOGPOINT_SILENT)
#define LOGPOINT_IS_BROKEN(lp)              LOGPOINT_FLAG((lp), LOGPOINT_BROKEN)
#define LOGPOINT_IS_DYNAMIC_CODE(lp)        LOGPOINT_FLAG((lp), LOGPOINT_DYNAMIC_CODE)
#define LOGPOINT_IS_HARD(lp)                LOGPOINT_FLAG((lp), LOGPOINT_HARD)
#define LOGPOINT_IS_ACTIVE(lp)              LOGPOINT_FLAG((lp), LOGPOINT_ACTIVE)

/* incomplete */
#define LOGPOINT_SET_BACKTRACE(lp,flag)     LOGPOINT_SET_FLAG((lp), LOGPOINT_BACKTRACE, (flag))
#define LOGPOINT_SET_SILENT(lp,flag)        LOGPOINT_SET_FLAG((lp), LOGPOINT_SILENT, (flag))
#define LOGPOINT_SET_BROKEN(lp,flag)        LOGPOINT_SET_FLAG((lp), LOGPOINT_BROKEN, (flag))
#define LOGPOINT_SET_DYNAMIC_CODE(lp,flag)  LOGPOINT_SET_FLAG((lp), LOGPOINT_DYNAMIC_CODE, (flag))
#define LOGPOINT_SET_HARD(lp,flag)          LOGPOINT_SET_FLAG((lp), LOGPOINT_HARD, (flag))
#define LOGPOINT_SET_ACTIVE(lp,flag)        LOGPOINT_SET_FLAG((lp), LOGPOINT_ACTIVE, (flag))

#define LOGPOINT_DISABLE(lp)                LOGPOINT_SET_ACTIVE((lp), 0)
#define LOGPOINT_ENABLE(lp)                 LOGPOINT_SET_ACTIVE((lp), 1)

#define LOGPOINT_NOT_COUNTED                (-1) /* marker for count field if counting is disabled */

typedef int (*LOGPOINT_FILTER)(LOGPOINT *lp, void *workerInfo); /* return type may change soon */

typedef lp_return_t (*LOGPOINT_WORKER)(LOGPOINT *lp, void *workerInfo);

#endif 
/* __LOGPOINTS_TYPES_H__ */


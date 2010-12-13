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

#ifndef __LOGPOINTS_DEFAULT_POLICY_H__
#define __LOGPOINTS_DEFAULT_POLICY_H__

/* compile time feature enable defaults - make sure that these are always included before logpoints.h */

/* undef'ing this will disable all kinds of logging */
#ifndef LOGPOINT_ENABLE_LPLOG
#define LOGPOINT_ENABLE_LPLOG 1
#endif

#ifndef LOGPOINT_COUNT
#ifdef LOGPOINT_RELEASE_BUILD
#define LOGPOINT_COUNT 0
#else
#define LOGPOINT_COUNT 1
#endif
#endif

#ifndef LOGPOINT_ENABLE_TRACE
#define LOGPOINT_ENABLE_TRACE 1
#endif

#ifndef LOGPOINT_ENABLE_ASSERT
#define LOGPOINT_ENABLE_ASSERT 1
#endif

#ifndef LOGPOINT_ENABLE_NOTES
#ifdef LOGPOINT_RELEASE_BUILD
#define LOGPOINT_ENABLE_NOTES 0
#else
#define LOGPOINT_ENABLE_NOTES 1
#endif
#endif

#ifndef LOGPOINT_ENABLE_SWITCH
#define LOGPOINT_ENABLE_SWITCH 1
#endif


#ifndef LOGPOINT_ENABLE_DEBUG
#define LOGPOINT_ENABLE_DEBUG 1
#endif

#ifndef LOGPOINT_ENABLE_INFO
#define LOGPOINT_ENABLE_INFO 1
#endif

#ifndef LOGPOINT_ENABLE_NOTICE
#define LOGPOINT_ENABLE_NOTICE 1
#endif

#ifndef LOGPOINT_ENABLE_WARNING
#define LOGPOINT_ENABLE_WARNING 1
#endif

#ifndef LOGPOINT_ENABLE_ERROR
#define LOGPOINT_ENABLE_ERROR 1
#endif

#ifndef LOGPOINT_ENABLE_CRITICAL
#define LOGPOINT_ENABLE_CRITICAL 1
#endif

#ifndef LOGPOINT_ENABLE_ALERT
#define LOGPOINT_ENABLE_ALERT 1
#endif

#ifndef LOGPOINT_ENABLE_EMERGENCY
#define LOGPOINT_ENABLE_EMERGENCY 1
#endif


/* default flag sets */

#define LOGPOINT_FLAGS_DEBUG        ( LOGPOINT_PRIORITIZED | LOGPOINT_DEBUG )
#define LOGPOINT_FLAGS_INFO         ( LOGPOINT_PRIORITIZED | LOGPOINT_INFO )
#define LOGPOINT_FLAGS_NOTICE       ( LOGPOINT_PRIORITIZED | LOGPOINT_NOTICE )
#define LOGPOINT_FLAGS_WARNING      ( LOGPOINT_PRIORITIZED | LOGPOINT_WARNING | LOGPOINT_HARD | LOGPOINT_ACTIVE )
#define LOGPOINT_FLAGS_ERROR        ( LOGPOINT_PRIORITIZED | LOGPOINT_ERROR | LOGPOINT_HARD | LOGPOINT_ACTIVE )
#define LOGPOINT_FLAGS_CRITICAL     ( LOGPOINT_PRIORITIZED | LOGPOINT_CRITICAL | LOGPOINT_HARD | LOGPOINT_ACTIVE )
#define LOGPOINT_FLAGS_ALERT        ( LOGPOINT_PRIORITIZED | LOGPOINT_ALERT | LOGPOINT_HARD | LOGPOINT_ACTIVE )
#define LOGPOINT_FLAGS_EMERGENCY    ( LOGPOINT_PRIORITIZED | LOGPOINT_EMERGENCY | LOGPOINT_HARD | LOGPOINT_ACTIVE )

#define LOGPOINT_FLAGS_TRACE        ( LOGPOINT_DEBUG )
#define LOGPOINT_FLAGS_NOTE         ( LOGPOINT_NOTE )

#define LOGPOINT_FLAGS_SWITCH       ( LOGPOINT_SWITCH ) /* SILENT flag depends on number of arguments to macro */

#define LOGPOINT_FLAGS_ASSERT       ( LOGPOINT_EMERGENCY | LOGPOINT_ASSERT | LOGPOINT_HARD | LOGPOINT_ACTIVE )

#endif
/* __LOGPOINTS_DEFAULT_POLICY_H__ */

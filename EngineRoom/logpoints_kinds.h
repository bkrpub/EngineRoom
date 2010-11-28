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

#ifndef __LOGPOINTS_DEFAULT_KINDS_H__
#define __LOGPOINTS_DEFAULT_KINDS_H__ 1

/* the following constants must be declared as char[] to be used in static initializers */

/* syslog equivalents */
LOGPOINT_EXTERN_C(kLogPointKindDebug[],     const char, "DEBUG");
LOGPOINT_EXTERN_C(kLogPointKindInfo[],      const char, "INFO");
LOGPOINT_EXTERN_C(kLogPointKindNotice[],    const char, "NOTICE");
LOGPOINT_EXTERN_C(kLogPointKindWarning[],   const char, "WARNING");
LOGPOINT_EXTERN_C(kLogPointKindError[],     const char, "ERROR");
LOGPOINT_EXTERN_C(kLogPointKindCritical[],  const char, "CRITICAL");
LOGPOINT_EXTERN_C(kLogPointKindAlert[],     const char, "ALERT");
LOGPOINT_EXTERN_C(kLogPointKindEmergency[], const char, "EMERGENCY");

LOGPOINT_EXTERN_C(kLogPointKindTrace[],     const char, "TRACE");

LOGPOINT_EXTERN_C(kLogPointKindNote[],      const char, "NOTE");
LOGPOINT_EXTERN_C(kLogPointKindFixMe[],     const char, "FIXME");
LOGPOINT_EXTERN_C(kLogPointKindToDo[],      const char, "TODO");

LOGPOINT_EXTERN_C(kLogPointKindSwitch[],    const char, "SWITCH");

LOGPOINT_EXTERN_C(kLogPointKindAssert[],    const char, "ASSERT");


#define kLogPointKindNone	NULL
#define kLogPointKeysNone	NULL
#define kLogPointLabelNone	NULL
#define kLogPointFormatNone	NULL
#define kLogPointFormatInfoNone NULL

#endif
/* __LOGPOINTS_DEFAULT_H__ */

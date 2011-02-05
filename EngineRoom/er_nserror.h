/*
 Copyright (c) 2010, Bjoern Kriews
 All rights reserved.
 
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

#ifndef __ER_NSERROR_H__
#define __ER_NSERROR_H__ 1

#import "er_localized.h"

#define ER_SET_NSERROR(errorPtr, theDomain, theCode, userInfoObjectsAndKeys, ...) \
do { if( nil != errorPtr ) \
*(errorPtr) = [NSError errorWithDomain: (theDomain) code: (theCode) userInfo: (userInfoObjectsAndKeys) ? [NSDictionary dictionaryWithObjectsAndKeys: (userInfoObjectsAndKeys), ## __VA_ARGS__, nil] : nil]; \
} while(0)

#define ER_PRESENT_NSERROR_REASON(presenter, theDomain, theCode, reasonFormat, ...) \
({ NSError *__presentError = nil; \
ER_SET_NSERROR((&__presentError), (theDomain), (theCode), ER_LOCALIZED_FORMAT(reasonFormat, ## __VA_ARGS__), NSLocalizedFailureReasonErrorKey); \
if( nil != __presentError ) { [((presenter) ? (NSResponder *)(presenter) : NSApp) presentError: __presentError]; } })

#define ER_SET_NSERROR_REASON(errorPtr, theDomain, theCode, reasonFormat, ...) \
ER_SET_NSERROR((errorPtr), (theDomain), (theCode), ER_LOCALIZED_FORMAT(reasonFormat, ## __VA_ARGS__), NSLocalizedFailureReasonErrorKey)

#define ER_CHECK_NSERROR_REASON(assertion, errorPtr, theDomain, theCode, reasonFormat, ...) \
({ BOOL __check = YES; if( ! (assertion) ) { ER_SET_NSERROR_REASON((errorPtr), (theDomain), (theCode), (reasonFormat), ## __VA_ARGS__); __check = NO; } __check; })			

#define ER_CHECK_NSERROR_REASON_RETURN_NIL(assertion, errorPtr, theDomain, theCode, reasonFormat, ...) \
do{ if( NO == ER_CHECK_NSERROR_REASON((assertion), (errorPtr), (theDomain), (theCode), (reasonFormat), ## __VA_ARGS__) ) { return nil; } } while(0)

#define ER_CHECK_NSERROR_REASON_RETURN_NO(assertion, errorPtr, theDomain, theCode, reasonFormat, ...) \
do{ if( NO == ER_CHECK_NSERROR_REASON((assertion), (errorPtr), (theDomain), (theCode), (reasonFormat), ## __VA_ARGS__) ) { return NO; } } while(0)

#endif 
/* __ER_NSERROR_H__ */ 

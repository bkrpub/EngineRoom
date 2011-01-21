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

#define __LOGPOINTS_C__ 1

/* #define SELF_TRACE(fmt, ...) fprintf(stderr, "TRC: "##fmt##"\n", __VA_ARGS__) */
#define SELF_TRACE(fmt, ...) /**/


#include "logpoints_api.h"

/* to define the symbols */
#include "logpoints_default_kinds.h"

#include "er_compat.h"


#ifdef __APPLE_CC__
#pragma mark Getting and setting LogPoint handlers
#endif

static char _logPointLogFormatDefault[] = "%#W|%T|.%#.3U %?%< %k %N %>[%K%<]%< O:%O #O: %#O %S %s <%f:%e> DEFAULT";

/* private - might be replaced by thread-local stuff */
static LOGPOINT_INVOKER    _logPointInvoker    = ER_SYMBOL_EMBEDDED_NAME(logPointInvokerDefault);
static LOGPOINT_COMPOSER   _logPointComposer   = ER_SYMBOL_EMBEDDED_NAME(logPointComposerDefault);
static LOGPOINT_EMITTER    _logPointEmitter    = ER_SYMBOL_EMBEDDED_NAME(logPointEmitterDefault);
static LOGPOINT_FORMATTERV _logPointFormatterV = ER_SYMBOL_EMBEDDED_NAME(logPointFormatterVDefault);

static const char *_logPointLogFormat = _logPointLogFormatDefault;

ER_SYMBOL_VISIBLE_EMBEDDED LOGPOINT_INVOKER ER_SYMBOL_EMBEDDED_NAME( logPointGetInvoker )(void) 
{ 
	return _logPointInvoker;
}

ER_SYMBOL_VISIBLE_EMBEDDED LOGPOINT_INVOKER ER_SYMBOL_EMBEDDED_NAME( logPointSetInvoker )(LOGPOINT_INVOKER newInvoker) 
{ 
	LOGPOINT_INVOKER previousInvoker = _logPointInvoker;
	_logPointInvoker = newInvoker ? newInvoker : ER_SYMBOL_EMBEDDED_NAME(logPointInvokerDefault);
	return previousInvoker;
}

ER_SYMBOL_VISIBLE_EMBEDDED LOGPOINT_COMPOSER ER_SYMBOL_EMBEDDED_NAME( logPointGetComposer )(void)
{
	return _logPointComposer;
}

ER_SYMBOL_VISIBLE_EMBEDDED LOGPOINT_COMPOSER ER_SYMBOL_EMBEDDED_NAME( logPointSetComposer )(LOGPOINT_COMPOSER newComposer)
{
	LOGPOINT_COMPOSER previousComposer = _logPointComposer;
	_logPointComposer = newComposer ? newComposer : ER_SYMBOL_EMBEDDED_NAME(logPointComposerDefault);
	return previousComposer;
}

ER_SYMBOL_VISIBLE_EMBEDDED LOGPOINT_EMITTER ER_SYMBOL_EMBEDDED_NAME( logPointGetEmitter )(void)
{
	return _logPointEmitter;
}

ER_SYMBOL_VISIBLE_EMBEDDED LOGPOINT_EMITTER ER_SYMBOL_EMBEDDED_NAME( logPointSetEmitter )(LOGPOINT_EMITTER newEmitter)
{
	LOGPOINT_EMITTER previousEmitter = _logPointEmitter;
	_logPointEmitter = newEmitter ? newEmitter : ER_SYMBOL_EMBEDDED_NAME(logPointEmitterDefault);
	return previousEmitter;
}

ER_SYMBOL_VISIBLE_EMBEDDED LOGPOINT_FORMATTERV ER_SYMBOL_EMBEDDED_NAME( logPointGetFormatterV )(void)
{
	return _logPointFormatterV;
}

ER_SYMBOL_VISIBLE_EMBEDDED LOGPOINT_FORMATTERV ER_SYMBOL_EMBEDDED_NAME( logPointSetFormatterV )(LOGPOINT_FORMATTERV newFormatterV)
{
	LOGPOINT_FORMATTERV previousFormatterV = _logPointFormatterV;
	_logPointFormatterV = newFormatterV ? newFormatterV : ER_SYMBOL_EMBEDDED_NAME(logPointFormatterVDefault);
	return previousFormatterV;
}

ER_SYMBOL_VISIBLE_EMBEDDED const char * ER_SYMBOL_EMBEDDED_NAME( logPointGetLogFormat )(void)
{
	return _logPointLogFormat;
}

ER_SYMBOL_VISIBLE_EMBEDDED const char * ER_SYMBOL_EMBEDDED_NAME( logPointSetLogFormat )(const char * newFormat)
{
	const char * previousLogFormat = _logPointLogFormat;
	_logPointLogFormat = newFormat ? newFormat : ER_SYMBOL_EMBEDDED_NAME(_logPointLogFormatDefault);
	return previousLogFormat;
}



#ifdef LOCAL_INVOKER
#warning clean up 

ER_SYMBOL_VISIBLE_EMBEDDED LOGPOINT_INVOKER_DECLARATION( ER_SYMBOL_EMBEDDED_NAME( logPointInvokerDefault ) )
{
#ifdef MAINTAINER_WARNINGS
#warning local client test
#warning no non-objc support
#endif  
	
	va_list args;
	va_start(args, fmt);
	
	NSString *msg = nil;
	
	if( nil != fmt ) {
		NSString *nsfmt = LOGPOINT_IS_NSSTRING(*lpp) ? (id)fmt : [[NSString alloc] initWithUTF8String: (const char *)fmt];
		
		msg = [[NSString alloc] initWithFormat: nsfmt arguments: args];
		
		if( LOGPOINT_IS_NSSTRING(*lpp) ) {
			[nsfmt release];
		}
	}
	
	NSLog(@"%s: %s %@", __FUNCTION__, lpp->kind, msg ?: @"NO PAYLOAD");
	[msg release];
	
	va_end(args);
	return LOGPOINT_YES;
}

#endif
/* LOCAL_INVOKER */

ER_SYMBOL_VISIBLE_EMBEDDED LOGPOINT_INVOKER_DECLARATION( ER_SYMBOL_EMBEDDED_NAME( logPointInvokerDefault ) )
{
	lp_return_t ret = LOGPOINT_YES;
	SELF_TRACE("invoker1");
	void *msg = NULL;
	
	if( ! LOGPOINT_IS_SILENT( *lpp ) ) {
		
		LOGPOINT_COMPOSER composer = ER_SYMBOL_EMBEDDED_NAME( logPointGetComposer )();

		
		if( NULL != fmt ) {
			va_list args;
			va_start(args, fmt); 
			
#ifdef __OBJC__
			CFStringRef cfFmt = NULL;
			
			if( NO == LOGPOINT_IS_NSSTRING(*lpp) ) {
				SELF_TRACE("invoker2");
				cfFmt = CFStringCreateWithCStringNoCopy(kCFAllocatorDefault, (const char *) fmt, kCFStringEncodingUTF8, kCFAllocatorNull /* don't free */);
			} else {
				SELF_TRACE("invoker3");
				cfFmt = (CFStringRef) fmt;
			}
			
			msg = (void *) CFStringCreateWithFormatAndArguments(kCFAllocatorDefault, NULL /* fmtOptions */, cfFmt, args);
			SELF_TRACE("invoker4");
#else
			util_vasprintf((char **) &msg, fmt, args);
#endif
			//SELF_TRACE("invoker5 comp = %p\n", composer);      
			ret = (*composer)(lpp, langSpec1, langSpec2, msg);
			SELF_TRACE("invoker6");      
#ifdef __OBJC__
			if( NULL != cfFmt )
				CFRelease( cfFmt );
#endif
			
			va_end(args);
		} else {
			SELF_TRACE("invoker7 comp = %p\n", composer);      
			ret = (*composer)(lpp, langSpec1, langSpec2, NULL);
			SELF_TRACE("invoker8");      
		} /* fmt != NULL */
		
	} /* ! SILENT */
	
	
	if( LOGPOINT_IS_ASSERT(*lpp) ) {
#if DEPRECATED_ASSERTION_HANDLING
#ifdef __OBJC__    
		if( LOGPOINT_IS_OBJC(*lpp) ) {
			[[NSAssertionHandler currentHandler] handleFailureInMethod: (SEL)langSpec2 object: (id)langSpec1 file: [NSString stringWithUTF8String: lpp->file] lineNumber: (int) lpp->line description: @"%@", msg];
		} else {
			[[NSAssertionHandler currentHandler] handleFailureInFunction: [NSString stringWithUTF8String: lpp->symbolName] file: [NSString stringWithUTF8String: lpp->file] lineNumber: (int)lpp->line description: @"%@", msg];
		}
		fprintf(stderr, "Unexpected return from assertion handler\n");
		abort();
#else
		abort();
#endif
#endif
	}
	SELF_TRACE("invoker9");      
#if MAINTAINER_WARNINGS
#warning this will leak for assertion exceptions which are catched
#endif
	
	if( NULL != msg ) {
#ifdef __OBJC__
		CFRelease( (CFStringRef) msg);
#else
		free( msg );
#endif
	}
	
	SELF_TRACE("invoker10");      
	
	return ret;
}

#define LOGPOINT_PAYLOAD_FORMAT "%s"
ER_SYMBOL_VISIBLE_EMBEDDED LOGPOINT_COMPOSER_DECLARATION( ER_SYMBOL_EMBEDDED_NAME( logPointComposerDefault ) )
{
	char buffer1[512];
	char buffer2[512];
	
	const char *logFormat = ER_SYMBOL_EMBEDDED_NAME( logPointGetLogFormat )();
	
	if( NULL == logFormat || 0 == *logFormat ) {
		return LOGPOINT_NO;
	}
	
	char *payloadFormat = strstr(logFormat, LOGPOINT_PAYLOAD_FORMAT);
	char *postPayload = NULL;
	
	size_t outputSize;
	
	if( payloadFormat ) {
		postPayload = payloadFormat + sizeof(LOGPOINT_PAYLOAD_FORMAT) - 1;
		
		snprintf(buffer2, sizeof(buffer2), "%.*s", (int) (payloadFormat - logFormat), logFormat);

		outputSize = ER_SYMBOL_EMBEDDED_NAME( logPointFormat )(lpp, langSpec1, langSpec2, buffer1, sizeof(buffer1), NULL, NULL, buffer2);		

		if( *postPayload ) {
		   outputSize = ER_SYMBOL_EMBEDDED_NAME( logPointFormat )(lpp, langSpec1, langSpec2, buffer2, sizeof(buffer2), NULL, NULL, postPayload);
		} else {
			buffer2[0] = 0; 
		}
		
	} else {
		payload = LOGPOINT_MESSAGE_EMPTY;
		outputSize = ER_SYMBOL_EMBEDDED_NAME( logPointFormat )(lpp, langSpec1, langSpec2, buffer1, sizeof(buffer1), NULL, NULL, logFormat);				
		buffer2[0] = 0; 
	}
	
	LOGPOINT_EMITTER emitter = ER_SYMBOL_EMBEDDED_NAME( logPointGetEmitter )();
	
	lp_return_t ret = (*emitter)(lpp, langSpec1, langSpec2, "%s" LOGPOINT_MESSAGE_FORMAT "%s", buffer1, payload, buffer2); 		

	return ret;
}

static int _logPointShowInstanceInfo UTIL_UNUSED = 1;
ER_SYMBOL_VISIBLE_EMBEDDED LOGPOINT_COMPOSER_DECLARATION( ER_SYMBOL_EMBEDDED_NAME( logPointComposerDefaultOld ) )
{
#if MAINTAINER_WARNINGS
#warning no nssstringmode for keys and label yet
#endif
	const char *kind = (kLogPointKindNone == lpp->kind) ? "" : lpp->kind;
	const char *keys = (kLogPointKeysNone == lpp->keys) ? "" : lpp->keys;
	const char *label = (kLogPointLabelNone == lpp->label) ? "" : lpp->label;
#ifdef __OBJC__
	const char *methodName = NULL;
	const char *className = NULL;
	char *instanceInfo = NULL;
	BOOL isClassMethod = NO;
	SELF_TRACE("composer1");      
	if( LOGPOINT_IS_OBJC(*lpp) ) {
		id objcSelf = (id) langSpec1;	
		SEL objcCmd = (SEL) langSpec2; 
		SELF_TRACE("composer2 = %p\n", object_getClass);      		
        /* using weak symbols */
		Class objcClass = COMPAT_OBJECT_GETCLASS(objcSelf);
		isClassMethod = COMPAT_CLASS_ISMETACLASS( objcClass );
		
		SELF_TRACE("composer3 = %p\n", object_getClassName);      		
		
		className = object_getClassName(objcSelf);
		
		SELF_TRACE("composer4 = %p\n", sel_getName);      		
		methodName = objcCmd ? sel_getName(objcCmd) : lpp->symbolName;
		
		char _instanceInfo[sizeof("0x0123456789abcdef:0123456789")];
		
		if( _logPointShowInstanceInfo && NO == isClassMethod ) {
			snprintf(_instanceInfo, sizeof(_instanceInfo), "%p:%u", (void*)objcSelf, (unsigned int) [objcSelf retainCount]);
			_instanceInfo[ sizeof(_instanceInfo) - 1] = 0;
			instanceInfo = _instanceInfo;
		}
	}
	SELF_TRACE("composer5");      		  
#endif
	SELF_TRACE("composer6 emit = %p\n", logPointGetEmitter());      		  

	const char *embedded_name = ER_EMBEDDED_NAME_AS_STRING;
	
	LOGPOINT_EMITTER emitter = ER_SYMBOL_EMBEDDED_NAME( logPointGetEmitter )();
	
	lp_return_t ret = (*emitter)(lpp, langSpec1, langSpec2, "%s%s%s %s%s%s<%s:%llu> %s%s%s%s%s %s%s%s%s" LOGPOINT_MESSAGE_FORMAT, 
											  embedded_name,
											  *embedded_name ? " " : "",
											  kind, 
											  *keys ? "[" : "", keys, *keys ? "] " : "", 
											  logPointLastPathComponent(lpp->file), (unsigned long long)lpp->line, 
#ifdef __OBJC__
											  className ? (isClassMethod ? "+[" : "-[") : "", 
											  className ? className : "", 
											  className ? " " : "", 
											  methodName ? methodName : lpp->symbolName, 
											  className ? "]" : "",
											  instanceInfo ? instanceInfo : "",
											  instanceInfo ? " " : "",
#else
											  "",
											  "",
											  "",
											  lpp->symbolName,
											  "", 
											  "",
											  "",
#endif
											  label, *label && payload ? " " : "", payload ? payload : LOGPOINT_MESSAGE_EMPTY);
	
	SELF_TRACE("composer7");      		  
	return ret;
}


#if 0
ER_SYMBOL_VISIBLE_EMBEDDED LOGPOINT_FORMAT_FUNCTION_DECLARATION( ER_SYMBOL_EMBEDDED_NAME( logPointFormatterUnused ) )
{
}
#endif

/* extensions and userInfo are not yet implemented, pass NULL, NULL - args not yet used */
ER_SYMBOL_VISIBLE_EMBEDDED LOGPOINT_FORMATTERV_DECLARATION( ER_SYMBOL_EMBEDDED_NAME( logPointFormatterVDefault ) ) 
{
	char tmp[ 64 ]; /* buffer for secondary formatting */ 

	char *endbuffer = buffer + bufferSize - 1;
	char *cursor = buffer;
	const char *fmt = format;
	const char *endfmt = fmt + strlen(fmt);
	
	const char *lastValue = NULL;
	int prefixLength = 0;

	struct timeval time_timeval = { 0, 0 };
	double time_double = 0.0;
	struct tm time_tm;
	
	for( cursor = buffer ; cursor < endbuffer && fmt < endfmt ; ++fmt ) {
		
		if( '%' != *fmt ) { /* also copies the final 0 */
			*cursor++ = *fmt;
			continue;
		}

		const char *startFmt = fmt;
		
		const char *value = NULL;
		int valueLength = -1; /* default - up to \0 */

		int tmpInt;
		
		int negateCondition = LOGPOINT_NO;

		int alternateForm = LOGPOINT_NO;

		int zeroPadding = LOGPOINT_NO;
		
		int negativeWidth = LOGPOINT_NO;		
		
		int alwaysSigned = LOGPOINT_NO;		
		
		int positivePadding = LOGPOINT_NO;
		
		int separateThousands = LOGPOINT_NO;				

		int position = 0;
		
		int width = -1;
		int widthAsterisk = LOGPOINT_NO;
		
		int precision = -1;
		int precisionAsterisk = LOGPOINT_NO;
		
		char altivecSeparator = 0;

		int shortModifier = 0; /* 0 1 2 */
		int longModifier = 0;  /* " " " */
		int longDoubleModifier = LOGPOINT_NO;
		int intmaxtModifier = LOGPOINT_NO;
		int ptrdifftModifier = LOGPOINT_NO;
		int quadModifier = LOGPOINT_NO;
		int sizetModifier = LOGPOINT_NO;

		char delimiter; /* for %W|| */
		char *nextDelimiter = NULL;
		
		int doneWithOptions = LOGPOINT_NO;
		
		++fmt; /* skip % */
		
		do {
			switch( *fmt ) {
				case '#':
					alternateForm = YES;
					++fmt;
					break;
				
				case '0':
					zeroPadding = LOGPOINT_YES;
					++fmt;
					break;
					
				case '-':
					negativeWidth = LOGPOINT_YES;
					++fmt;
					break;
					
				case ' ':
					positivePadding = LOGPOINT_YES;
					++fmt;
					break;
					
				case '+':
					alwaysSigned = LOGPOINT_YES;
					++fmt;
					break;					

				case '\'':
					separateThousands = LOGPOINT_YES;
					++fmt;
					break;					

				case '*':
					widthAsterisk = LOGPOINT_YES;
					++fmt;
					break;
					
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					tmpInt = (int) strtol(fmt, (char **) &fmt, 10); /* bad: handles +- / space */
					if( '$' == *fmt ) {
						position = tmpInt;
					} else {
						width = tmpInt;
					}
					break;

				case '.':
					++fmt;
					if( '*' == *fmt ) {
						precisionAsterisk = LOGPOINT_YES;
						++fmt;
					} else {
						precision = (int) strtol(fmt, (char **) &fmt, 10); /* bad: handles +- / space */
					}
					break;
					
				case 'h':
					++shortModifier;
					++fmt;
					break;
					
				case 'l':
					++longModifier;
					++fmt;
					break;
					
				case 'L':
					longDoubleModifier = LOGPOINT_YES;
					++fmt;
					break;
					
				case 'j':
					intmaxtModifier = LOGPOINT_YES;
					++fmt;
					break;					
					
				case 'q': /* deprecated */
					quadModifier = LOGPOINT_YES;
					++fmt;
					break;					

				case 't':
					ptrdifftModifier = LOGPOINT_YES;
					++fmt;
					break;					
					
				case 'z':
					sizetModifier = LOGPOINT_YES;
					++fmt;
					break;					
				
					
				case ',': /* altivec separator extension */
				case ';':
				case ':':
				case '_':
					altivecSeparator = *fmt++;
					break;
					
				case '!': /* logpoints extension */
					negateCondition = LOGPOINT_YES;
					++fmt;
					break;
					
				default:
					doneWithOptions = YES;
					break;
			}
		} while( LOGPOINT_NO == doneWithOptions );
		
				
		if( negativeWidth && zeroPadding ) {
			zeroPadding = LOGPOINT_NO;
		}

		if( alwaysSigned && positivePadding ) {
			positivePadding = LOGPOINT_NO;
		}
		
#ifdef MAINTAINER_WARNINGS
#warning position and asterisk (and many other features) are currently unimplemented - both are not relevant for this usage 
#endif
		
		char expander = *fmt;

		/* NOTE: %>[%t%!<-%<] will produce [%t] if %t != NULL, - otherwise */ 			
			
		if( '>' == expander ) { /* prefix next % expansion with next character if expansion is non-NULL */
			*cursor++ = *++fmt;
			++prefixLength;
			continue;
		}

		if( 0.0 == time_double && ( 'U' == expander || 'w' == expander || 'W' == expander ) ) {
			gettimeofday(&time_timeval, NULL);
			time_double = time_timeval.tv_sec + 1.0e-6 * time_timeval.tv_usec;
		}
		

		size_t spaceLeft = (size_t) (endbuffer - cursor);
		
		
		/* do NOT use printf options chars ( ! + - space _:;, h l L q z t j ' . 0-9 * # ) */
		switch( expander ) { 
				
			case 'A': /* address */
				snprintf(tmp, sizeof(tmp), "%p", lpp->address);
				value = tmp;
				break;																		
			
			case 'b': /* binary filename (without path) / %#b with */					
				value = alternateForm ? lpp->image : logPointLastPathComponent( lpp->image );
				break;

			case 'B': /* label or %#B for formatInfo */
				value = alternateForm ? lpp->formatInfo : lpp->label;
				break;														
				
			case 'C': /* class or %#C for class with category */
				//value = className;
				break;																		

			case 'e': /* line number */
				snprintf(tmp, sizeof(tmp), "%-*llu", width == -1 ? 1 : width, (unsigned long long) lpp->line);
				value = tmp;
				break;										
				
			case 'f': /* filename */					
				value = alternateForm ? lpp->file : logPointLastPathComponent( lpp->file );
				break;
				
			case 'F': /* flags */					
				value = "NOT YET";
				break;				

			case 'i': /* uid %#i euid */					
				snprintf(tmp, sizeof(tmp), "%llu", (unsigned long long) ( alternateForm ? getegid() : getgid() ) );
				value = tmp;
				break;								
				
			case 'I': /* gid %#I egid */					
				snprintf(tmp, sizeof(tmp), "%llu", (unsigned long long) ( alternateForm ? getegid() : getgid() ) );
				value = tmp;
				break;												
			
			case 'k': /* kind, need to add upper/lower */
				value = lpp->kind;
				break;										

			case 'K': /* keys */
				value = lpp->keys;
				break;																		
		
				
			case 'M': /* method */
#if __OBJC__						
#if MAINTAINER_WARNINGS
#warning use symbolName
#endif
				if( NULL != langSpec2 ) {
					value = sel_getName( (SEL) langSpec2 );
				}
#endif						
				break;																		
				
			case 'N': /* number of passes/invocations (depends on LOGPOINT_COUNT_ALWAYS) */
				snprintf(tmp, sizeof(tmp), "%lld", (long long) lpp->count);
				value = tmp;
				break;																						

			case 'O': /* object info / %#O for class name */
				if( NULL != langSpec1 ) {
					if( alternateForm ) {
#if __OBJC__						
						value = object_getClassName( (id) langSpec1 );
#endif						
					} else {
						snprintf(tmp, sizeof(tmp), "%p", langSpec1);
						value = tmp;
					}

				}
				break;

			case 'p': /* priority %#p priorityname */					
				if( alternateForm ) {
					snprintf(tmp, sizeof(tmp), "%llu", (unsigned long long) LOGPOINT_PRIORITY(*lpp) );
					value = tmp;
				} else {
					value = logPointPriorityNameFromNumber( LOGPOINT_PRIORITY(*lpp) );
				}
				break;								
				
			case 'P': /* pid %#P ppid */					
				snprintf(tmp, sizeof(tmp), "%llu", (unsigned long long) ( alternateForm ? getppid() : getpid() ) );
				value = tmp;
				break;												

			case 'S': /* symbol */
				value = lpp->symbolName;
				break;						
				
			case 'T': /* thread */
				value = "NOT YET";
				break;
				
			case 'U': /* time (unixtime as double, %#w for usec, %#.3w for msec ) */				
				if( alternateForm ) {
					snprintf(tmp, sizeof(tmp), "%.*lf", precision == -1 ? 6 : precision, time_double - floor(time_double));					
					value = tmp + 2;
				} else {
					snprintf(tmp, sizeof(tmp), "%*.*lf", width == -1 ? 17 : width, precision == -1 ? 6 : precision, time_double);					
					value = tmp;
				}
				break;				
				
			case 'W': /* when (formatted time, UTC, %#W for local, usage: %W|%Y-%m-%d %H:%M:%S| delimiter is arbitrary) */
				delimiter = *++fmt;
				
				if( 0 == delimiter || NULL == (nextDelimiter = strchr(++fmt, delimiter) ) ) {
					fmt = endfmt; /* crisis - bail out */
					value = "?{%W needs delimiters - i.e. %W|%F|}";
				} else {
				
					if( (int) sizeof(tmp) <= snprintf(tmp, sizeof(tmp), "%.*s", (int) (nextDelimiter - fmt), fmt) ) {
						fmt = endfmt; /* crisis - bail out */
						value = "?{%W format too long}";
					} else {

						if( alternateForm ) {
							localtime_r(&time_timeval.tv_sec, &time_tm);
						} else {
							gmtime_r(&time_timeval.tv_sec, &time_tm);
						}
								
						cursor += strftime(cursor, spaceLeft, tmp, &time_tm); /* returns 0 on failure */
						fmt = nextDelimiter; /* skip internal format, delimiter is skipped by for loop */
						/* not using value */
					}
				}
						
			   break;										
				
			case '?': /* embedded name */
				value = *ER_EMBEDDED_NAME_AS_STRING ? ER_EMBEDDED_NAME_AS_STRING : ( alternateForm ? "MAIN" : NULL );
				break;
				
			case '<': /* output next character if previous % expansion was non-NULL, > is handled above */
				++fmt;
				if( negateCondition ? NULL == lastValue : NULL != lastValue ) {
					*cursor++ = *fmt;
				}
				break;				
								
			case '%': /* literal % */
				*cursor++ = '%';
				break;
				
			default: /* ignore %, handle as literal */
				snprintf(tmp, sizeof(tmp), "?{%.*s}", (int) (fmt - startFmt), startFmt);
				value = tmp;				
				break;

		} // switch *fmt
		
		if( NULL != value && 0 == *value ) {
			value = NULL;
		}
		
		if( prefixLength ) {
			if( negateCondition ? NULL != value : NULL == value ) {
				cursor -= prefixLength; /* "erase" written prefix if not wanted */
			}

			prefixLength = 0;
		}
		
		if( NULL != value ) {
			
#if 0			
			size_t spaceNeeded = ( valueLength == -1 ) ? strlen( value ) : (size_t) valueLength;
			
			if( spaceNeeded >= spaceLeft ) {
				break;
			} else {
		
				strncpy(cursor, value, spaceNeeded);
				cursor += spaceNeeded;
			}
#else
			if( -1 == precision && -1 != valueLength ) {
				precision = valueLength;
			}
			
			if( -1 != precision && -1 != valueLength && valueLength < precision ) {
				precision = valueLength;
			}
			
			size_t spaceNeeded = snprintf(cursor, spaceLeft, "%*.*s", 
										width == -1 ? 0 : negativeWidth ? -width : width, 
										  precision == -1 ? (int) strlen(value) : precision,
										  value);

			cursor += strlen(cursor);
			
			if( spaceNeeded >= spaceLeft ) {
				break;
			}
#endif
		
		}
			
		if( '<' != expander ) { /* keep lastValue alive as long as we are producing trailing characters */
			lastValue = value;			
		}

	} // for cursor 

	*cursor = '\0';

#ifdef MAINTAINER_WARNINGS
#warning better return the size IF we had enough space like snprintf - then again its expensive
#endif
	return (size_t) (cursor - buffer);
}

ER_SYMBOL_VISIBLE_EMBEDDED LOGPOINT_FORMATTER_DECLARATION( ER_SYMBOL_EMBEDDED_NAME( logPointFormat ) ) 
{
	va_list args;
	va_start(args, format);
	
	LOGPOINT_FORMATTERV formatterv = ER_SYMBOL_EMBEDDED_NAME( logPointGetFormatterV )();

	size_t written = (*formatterv)(lpp, langSpec1, langSpec2, buffer, bufferSize, extensions, userInfo, format, args);
	va_end(args);
	return written;
}


ER_SYMBOL_VISIBLE_EMBEDDED LOGPOINT_EMITTER_DECLARATION( ER_SYMBOL_EMBEDDED_NAME( logPointEmitterDefault ) )
{
	va_list args;
	va_start(args, fmt);
	
	lp_return_t ret = LOGPOINT_YES;
	
#ifdef __OBJC__
	CFStringRef cfFmt = CFStringCreateWithCStringNoCopy(kCFAllocatorDefault, fmt, kCFStringEncodingUTF8, kCFAllocatorNull /* don't free */);  
	NSLogv((NSString*) cfFmt, args);
	CFRelease(cfFmt);
#else
	char *log = NULL;
	
	int len = util_log_vasprintf(&log, fmt, args);
	if( len+1 != fprintf(stderr, "%s\n", log) )
		ret = LOGPOINT_NO;
	
	free(log);
#endif
	
	va_end(args);
	
	return ret;
}


#ifndef ER_EMBEDDED_NAME


#ifdef __APPLE_CC__
#pragma mark Private interface (currently unused)
#endif

static LOGPOINT *__logPointListHead = NULL;

LOGPOINT *_logPointListHead(void);

LOGPOINT *_logPointListHead(void)
{
  return __logPointListHead;
}



#ifdef __APPLE_CC__
#pragma mark Functions to be used with logpoints at runtime
#endif

#if MAINTAINER_WARNINGS
#warning BK: make these use the kind constants
#endif
static const char *logPointPriorityNames[] = { "EMERGENCY", "ALERT", "CRITICAL", "ERROR", "WARNING", "NOTICE", "INFO", "DEBUG" };

const char *logPointPriorityNameFromNumber(lp_uint_t priority)
{
  return priority < 0 || priority >= (long) (sizeof(logPointPriorityNames)/sizeof(logPointPriorityNames[0])) ? "BAD_PRIORITY" : logPointPriorityNames[priority];
}

lp_uint_t logPointPriorityNumberFromName(const char *name)
{
  unsigned int i;
  for( i = 0 ; i < sizeof(logPointPriorityNames)/sizeof(logPointPriorityNames[0]) ; ++i ) {
    if( 0 == strcasecmp(name, logPointPriorityNames[i] ) )
      return i;
  }

  return -1;
}

const char *logPointLastPathComponent(const char *path)
{
	if( NULL == path ) {
		return NULL;
	}
		
  const char *file = strrchr(path, UTIL_PATH_SEPARATOR);
  
  if( NULL == file || '\0' == file[1] )
    file = path;
  else
    ++file;

  return file;
}

const char *logPointReturnString(lp_return_t err)
{
  switch(err) {
  case LOGPOINT_RETURN_STOP:
    return "LOGPOINT_RETURN_STOP";

  case LOGPOINT_RETURN_OK:
    return "LOGPOINT_RETURN_OK";
  case LOGPOINT_RETURN_BAD_ALIGNMENT:
    return "LOGPOINT_RETURN_BAD_ALIGNMENT";
  case LOGPOINT_RETURN_BAD_MAGIC:
    return "LOGPOINT_RETURN_BAD_MAGIC";
  case LOGPOINT_RETURN_BAD_SIZE:
    return "LOGPOINT_RETURN_BAD_SIZE";
  case LOGPOINT_RETURN_BAD_STRUCTURE:
    return "LOGPOINT_RETURN_BAD_STRUCTURE";
  case LOGPOINT_RETURN_UNEXPECTED_SIZE:
    return "LOGPOINT_RETURN_UNEXPECTED_SIZE";
  case LOGPOINT_RETURN_NO_IMAGE_LIST:
    return "LOGPOINT_NO_IMAGE_LIST";
  case LOGPOINT_RETURN_NO_IMAGE_NAME:
    return "LOGPOINT_NO_IMAGE_NAME";
  case LOGPOINT_RETURN_BAD_FILTER:
   return "LOGPOINT_RETURN_BAD_FILTER";
  }
  
  return "LOGPOINT_RETURN_UNKNOWN";
}

lp_return_t logPointReset(void) { return logPointDisableSimple(""); }
lp_return_t logPointEnableSimple(const char *filter) { return logPointApplySimple(filter, LOGPOINT_OPTION_ENABLE); }
lp_return_t logPointDisableSimple(const char *filter) { return logPointApplySimple(filter, LOGPOINT_OPTION_DISABLE); }

lp_return_t logPointApplySimple(const char *filter, lp_uint_t options)
{
/*fprintf(stderr, "%s\n", __UTIL_PRETTY_FUNCTION__); */

  if( NULL == filter ) 
    return LOGPOINT_RETURN_OK;

  return logPointApply( logPointFilterSimple /*filter*/, (void*) filter, NULL /*action*/, NULL /*actionInfo*/, options);
}

lp_return_t logPointDumpAllWithFormat(const char *format)
{
  return logPointApply(NULL /*filter*/, NULL /*filterInfo*/, logPointActionDumpWithFormat /*action*/, (void *) format /*actionInfo*/, LOGPOINT_OPTION_NONE);
}

lp_return_t logPointActionDumpWithFormat(LOGPOINT *lpp, void *actionInfo)
{
	char *format = actionInfo;
	char buffer[512];
	
	size_t outputSize = logPointFormat(lpp, NULL, NULL, buffer, sizeof(buffer), NULL, NULL, format);
	
	NSLog(@"%s", buffer);
	//fprintf(stderr, "s: %3ld o: %s\n", (long) outputSize, buffer );  
	
	return LOGPOINT_RETURN_OK;
}

lp_return_t logPointDumpAll(void)
{
/*fprintf(stderr, "%s\n", __UTIL_PRETTY_FUNCTION__); */

  return logPointApply(NULL /*filter*/, NULL /*filterInfo*/, logPointActionDump /*action*/, NULL /*actionInfo*/, LOGPOINT_OPTION_NONE);
}

lp_return_t logPointActionDump(LOGPOINT *lpp, void *actionInfo UTIL_UNUSED)
{
    const char *keys = lpp->keys ? lpp->keys: "";
	const char *file = logPointLastPathComponent(lpp->file);

	int formatInfoLen = 1;

	/* remove ", " at EOL from using '#fmt ", " #__VA_ARGS__' with no arguments */
	if( NULL != lpp->formatInfo ) {
	  formatInfoLen = (int) strlen(lpp->formatInfo);
	  if( formatInfoLen > 1 && ',' == lpp->formatInfo[formatInfoLen - 2] && ' ' == lpp->formatInfo[formatInfoLen - 1] )
	    formatInfoLen -= 2;
	}

	fprintf(stderr, "LOGPOINT: %s %s%s%s%s %s:%llu %s %p %s %.*s\n", 
		LOGPOINT_IS_ACTIVE(*lpp) ? "ON " : "OFF", 
		lpp->kind, *keys ? " [" : "", keys, *keys ? "]" : "", 
		file, (unsigned long long)lpp->line, lpp->symbolName, lpp->address, 
		lpp->label ? lpp->label : "-", formatInfoLen, lpp->formatInfo ? lpp->formatInfo : "-");

	return LOGPOINT_RETURN_OK;
}

int logPointFilterSimple(LOGPOINT *lpp, void *filterInfo)
{
	char *filter = filterInfo;
	/*fprintf(stderr, "%s (%s)\n", __UTIL_PRETTY_FUNCTION__, filter); */
	
	if( NULL == filter )
		return LOGPOINT_NO;
	
	size_t filterLen = strlen(filter);
	
	if( 0 == filterLen )
		return LOGPOINT_YES;
	
	char *begin = filter;
	char *end;
	
	do {
		end = strchr(begin, ',');
		
		char *realEnd = end ? end : &filter[filterLen];
		size_t len = realEnd - begin;
		
		if( lpp->keys ) {
			const char *tmp = lpp->keys;
			while(*tmp) {
				if( 0 == strncmp(tmp, begin, len ) ) {
					return LOGPOINT_YES;
				}
				
				++tmp;
			}
		}
		
		begin = realEnd + 1;
		
	} while( end );
	
	
	return LOGPOINT_NO;
}


lp_return_t logPointApplyToData(const char *imageName, LOGPOINT *logpts, size_t logSizeInBytes, 
	LOGPOINT_FILTER filter, void *filterInfo, LOGPOINT_WORKER action, void *actionInfo, lp_uint_t options)
{
/*fprintf(stderr, "%s\n", __UTIL_PRETTY_FUNCTION__); */
    unsigned int brokenLogPoints = 0;
	
    if( sizeof(LOGPOINT) != LOGPOINT_EXPECTED_SIZE ) 
        return LOGPOINT_RETURN_UNEXPECTED_SIZE;
	
    if( ! logpts || ! logSizeInBytes )
        return 0;
    
    size_t nlogs = logSizeInBytes / sizeof(LOGPOINT);
    size_t rest = logSizeInBytes - sizeof(LOGPOINT) * nlogs;
    size_t nread = 0;
    
    if( rest != 0 )
        return LOGPOINT_RETURN_BAD_ALIGNMENT;
	
    if( logpts->magic != LOGPOINT_MAGIC )
        return LOGPOINT_RETURN_BAD_MAGIC;
	
    if( logpts->size != sizeof(LOGPOINT) )
        return LOGPOINT_RETURN_BAD_SIZE;
    
    while( nread != nlogs ) {
		
        if( logpts->magic != LOGPOINT_MAGIC )
            return LOGPOINT_RETURN_BAD_STRUCTURE;
		
		if( ! LOGPOINT_MAGIC_TEST(*logpts) ) {
			return LOGPOINT_RETURN_BAD_MAGIC;
		}
		
		LOGPOINT_SET_DYNAMIC_CODE(*logpts, options & LOGPOINT_OPTION_WALKING_DYNAMIC ? 1 : 0);
        
        logpts->image = imageName;
		
        if( LOGPOINT_IS_BROKEN(*logpts) ) {
            ++brokenLogPoints;
            fprintf(stderr, "logpoints: broken logpoint in %s - %s:%llu",
                    logpts->symbolName, logpts->file, (unsigned long long)logpts->line);
        }
		
        ++nread;
        
	if( 0 == ( options & LOGPOINT_OPTION_IGNORE_HARD ) || ! LOGPOINT_IS_HARD(*logpts) ) {
			
			if( filter == NULL || LOGPOINT_YES == (*filter)(logpts, filterInfo) ) {
				if( options & LOGPOINT_OPTION_DISABLE ) {
				  LOGPOINT_DISABLE(*logpts);
				} else if( options & LOGPOINT_OPTION_ENABLE ) {
				  LOGPOINT_ENABLE(*logpts);
				}

				if( NULL != action ) {
				  if( LOGPOINT_RETURN_STOP == (*action)(logpts, actionInfo ) ) { 
				    break;
				  }
				}
			}
			
		}
        ++logpts;
    }
    
	/* fprintf(stderr, "read %ld entries\n", nread); */
    
    if( brokenLogPoints != 0) {
        fprintf(stderr, "logpoints: detected %u broken logpoint%s, aborting",
                brokenLogPoints, brokenLogPoints > 1 ? "s" : "");
        abort();
    }
    
    return LOGPOINT_RETURN_OK;
}

lp_return_t logPointApply( LOGPOINT_FILTER filter, void *filterInfo, LOGPOINT_WORKER action, void *actionInfo, lp_uint_t options )
{
/*fprintf(stderr, "%s\n", __UTIL_PRETTY_FUNCTION__); */

  lp_return_t ret = logPointPlatformApply(filter, filterInfo, action, actionInfo, options);
  if( LOGPOINT_RETURN_OK != ret ) {
    fprintf(stderr, "logpoints: internal error (%s)\n", logPointReturnString(ret));
  }

  return ret;
}

#ifdef __APPLE__

#import <mach-o/dyld.h>
#import <mach-o/loader.h>
#import <mach-o/arch.h>
#import <mach-o/getsect.h>
#import <mach-o/ldsyms.h>
#import <mach-o/nlist.h>
#import <mach-o/stab.h>
#import <mach-o/fat.h>

lp_return_t logPointPlatformApply( LOGPOINT_FILTER filter, void *filterInfo, LOGPOINT_WORKER action, void *actionInfo, lp_uint_t options )
{
  const char *segname = LOGPOINT_SEGMENT;
  const char *sectname = LOGPOINT_SECTION;
    
    uint32_t i, numImages;
    const char *imageName;
    LOGPOINT *logpts;
    size_t logSizeInBytes;
    
    lp_return_t ret = LOGPOINT_RETURN_OK;
    
    numImages = _dyld_image_count();

    for( i = 0 ; i < numImages ; ++i ) {
        imageName = _dyld_get_image_name( i );
        
        /* skip system stuff, save time */
#if 1
        if( imageName )
            if( imageName == strstr(imageName, "/System") || imageName == strstr(imageName, "/usr") )
                continue;
#else
#warning OPTIMIZATION DISABLED
#endif
        intptr_t slide = _dyld_get_image_vmaddr_slide( i );

        /* this is the recommended method but it does not work from a framework */
	/* int walkingDynamic = ( mhp == &_mh_execute_header ) ? 0 : 1; */

	int walkingDynamic = ( slide == 0 ) ? 0 : 1;

	if( walkingDynamic && (options & LOGPOINT_OPTION_STATIC_ONLY))
	  continue;
	if( ! walkingDynamic && (options & LOGPOINT_OPTION_DYNAMIC_ONLY))
	  continue;

        /* docs say logSizeInBytes is unsigned long, header says uint32_t */
	const UTIL_MACH_HEADER *mhp = (UTIL_MACH_HEADER *) _dyld_get_image_header( i );
#ifdef __LP64__
	uint64_t logSizeTmp;
        logpts = (void *) getsectdatafromheader_64( mhp, segname, sectname, &logSizeTmp );
#else
	uint32_t logSizeTmp;
        logpts = (void *) getsectdatafromheader( mhp, segname, sectname, &logSizeTmp );
#endif

	logSizeInBytes = logSizeTmp;

        if( ! logpts ) /* no such section */
            continue;

        if( walkingDynamic ) 
            logpts = (LOGPOINT *) ((char *) logpts + slide); 

	/* fprintf(stderr, "%d: %s\n\tmh %p dyn: %d slide: %p log: %p siz: %ld\n", i, imageName, mhp, walkingDynamic, slide, logpts, logSizeInBytes); */
                
        ret = logPointApplyToData(imageName, logpts, logSizeInBytes, filter, filterInfo, action, actionInfo, options | (walkingDynamic ? LOGPOINT_OPTION_WALKING_DYNAMIC : 0));
	if( ret != LOGPOINT_RETURN_OK )
	  break;
    }
	
    return ret;
}    



#endif 
/* __APPLE__ */

#ifdef LOGPOINT_USE_ELF

#include <elf.h>
#include <limits.h>

/* for ElfW() cast macro and dl_iterate_phdr on linux */
#include <link.h>

Elf64_Addr getSectionFromELFObject(char *file, char *sectionName, int copy, size_t *lengthPtr);

#ifdef __sun
#if LOGPOINT_64BIT
#define LOGPOINT_ELF_ADDR Elf64_Addr
#else
#define LOGPOINT_ELF_ADDR Elf32_Addr
#endif
#endif

#ifdef __linux__
#define LOGPOINT_ELF_ADDR ElfW(Addr)
#endif


#ifdef __linux__
/* experimental */

struct logPointImageList { 
  int count;
  int capacity;
  const char **images; 
};

static int getImageListCallback(struct dl_phdr_info *info, size_t size, void *data)
{
#if BK_DEBUG
  fprintf(stderr, "getImageList: name='%s' addr=%p\n", info->dlpi_name, (void*) info->dlpi_addr);

  int j;
  for (j = 0; j < info->dlpi_phnum; j++)
                printf("\theader %2d: address=%10p\n", j,
                    (void *) (info->dlpi_addr + info->dlpi_phdr[j].p_vaddr));
#endif
  struct logPointImageList *list = data;

  if( list->capacity == 0 || list->count <= list->capacity - 1 ) {
    list->capacity = list->capacity ? list->capacity * 2 : 256;
    list->images = realloc(list->images, list->capacity * sizeof(const char *));
  }
  
  if( NULL == list->images ) {
    fprintf(stderr, "%s: could not allocate imageList\n", __UTIL_PRETTY_FUNCTION__);
    return 1;
  }
  
  list->images[ list->count ] = info->dlpi_name;

  ++list->count;

  return 0;
}

int getImageList(struct logPointImageList *imageList)
{
  imageList->count = 0;
  imageList->capacity = 0;
  imageList->images = NULL;

    if( 0 != dl_iterate_phdr(getImageListCallback, imageList) || 0 == imageList->count ) {

      if( NULL != imageList->images ) {
	free(imageList->images);
	imageList->images = NULL;
	return LOGPOINT_RETURN_NO_IMAGE_LIST;
      }
    }

    return LOGPOINT_RETURN_OK;
}

#endif
/* __linux__ experimental */

lp_return_t logPointPlatformApply( LOGPOINT_FILTER filter, void *filterInfo, LOGPOINT_WORKER action, void *actionInfo, lp_uint_t options )
{
  lp_return_t ret = LOGPOINT_RETURN_OK;

#ifdef __linux__
  struct logPointImageList imageList;

  ret = getImageList(&imageList);

  if( LOGPOINT_RETURN_OK != ret ) 
    return ret;
#endif

  size_t sectionLength;

#warning fragile method to get path of image    
    char imageName[PATH_MAX+1];
    imageName[0] = '\0';

#if defined( __sun ) || defined( __linux__ ) || defined( __BSD__ ) 

#if defined( __sun )
      char *platformPart = "/path/a.out";
#elif defined( __linux__ )
      char *platformPart = "/exe";
/*#elif defined( __BSD__ ) */
/*char *platformPart = "/file"; */
#endif

    char *linkName = NULL;
    util_asprintf(&linkName, "/proc/%llu%s", (unsigned long long)getpid(), platformPart);
    ssize_t imageNameLen = readlink(linkName, imageName, PATH_MAX);
    free(linkName);

    if( 0 < imageNameLen ) {
      imageName[imageNameLen] = 0;
    } else {
      imageName[0] = '\0';
    }

    if( ! imageName[0] ) {
      fprintf(stderr, "can not determine imageName - no /proc ?");
      return LOGPOINT_RETURN_NO_IMAGE_NAME;
    }
#else
#error no code to determine imageName for this platform
#endif


#warning walking of dynamic libraries not yet implemented
    LOGPOINT *logpts = (LOGPOINT *) (LOGPOINT_ELF_ADDR) getSectionFromELFObject(imageName, LOGPOINT_SECTION, 0, &sectionLength);

    /*fprintf(stderr, "logpts: %p\n", logpts); */

    if( NULL == logpts ) {
      fprintf(stderr, "%s: no logpoints in image\n", imageName);
      return ret;
    }

    ret = logPointApplyToData(imageName, logpts, sectionLength, filter, filterInfo, action, actionInfo, options);

    return ret;
}    

Elf32_Shdr *getELF32SectionHeader(void *mappedImage, const char *sectionName)
{
  Elf32_Ehdr *ehdr = mappedImage;
  unsigned char *image = mappedImage;

  Elf32_Shdr *shdr, *found = NULL;

  const char *sectionNames = (char *) image + ((Elf32_Shdr *) ( image + ehdr->e_shoff + ehdr->e_shstrndx * ehdr->e_shentsize ))->sh_offset;

  Elf32_Half idx;

  for( idx = 0 ; idx < ehdr->e_shnum ; ++idx ) {
    shdr = (Elf32_Shdr *) ( (char *) image + ehdr->e_shoff + idx * ehdr->e_shentsize );

    /*fprintf(stderr, "ELF 32bit Section %02d: %s\n", idx, &sectionNames[ shdr->sh_name ]); */

    if( 0 == strcmp(&sectionNames[ shdr->sh_name ], sectionName ) ) {
      found = shdr;
      break;
    }

  }

  return found;
}

Elf64_Shdr *getELF64SectionHeader(void *mappedImage, const char *sectionName)
{
  Elf64_Ehdr *ehdr = mappedImage;
  unsigned char *image = mappedImage;

  Elf64_Shdr *shdr, *found = NULL;

  const char *sectionNames = (char *) image + ((Elf64_Shdr *) ( image + ehdr->e_shoff + ehdr->e_shstrndx * ehdr->e_shentsize ))->sh_offset;

  Elf32_Half idx;

  for( idx = 0 ; idx < ehdr->e_shnum ; ++idx ) {
    shdr = (Elf64_Shdr *) ( (char *) image + ehdr->e_shoff + idx * ehdr->e_shentsize );

    /* fprintf(stderr, "ELF 64bit Section %02d: %s\n", idx, &sectionNames[ shdr->sh_name ]); */

    if( 0 == strcmp(&sectionNames[ shdr->sh_name ], sectionName ) ) {
      found = shdr;
      break;
    }

  }

  return found;
}


Elf64_Addr getSectionFromELFObject(char *file, char *sectionName, int copy, size_t *lengthPtr)
{
  size_t imageLength;
  void *image = util_map_image(file, &imageLength);

  void *shdr = NULL;

  Elf64_Addr sectionVirtualAddress = 0;
  void *theCopy = NULL;
  void *sectionInImage = NULL;
  size_t sectionLength = 0;

  if( lengthPtr )
    *lengthPtr = 0;

  if( NULL == image )
    utilReturnWithMessage(0, "can not map ELF image from file %s", file);

  if( 0 != strncmp(ELFMAG, image, strlen(ELFMAG)) )
    utilReturnWithMessage(0, "'%s' is not an ELF object", file);

  unsigned char elfClass = ((unsigned char *) image)[EI_CLASS];
 
  switch(elfClass) {
    case ELFCLASS32:
      {
	Elf32_Shdr *shdr32 = getELF32SectionHeader(image, sectionName);
	
	if( NULL != shdr32 ) {
	  shdr = shdr32;
	  sectionLength = (size_t) shdr32->sh_size;
	  sectionInImage = (void *) (image + shdr32->sh_offset);
	  sectionVirtualAddress = shdr32->sh_addr;
	}
      }
      break;
	
    case ELFCLASS64:
      {
	Elf64_Shdr *shdr64 = getELF64SectionHeader(image, sectionName);
	
	if( NULL != shdr64 ) {
	  shdr = shdr64;
	  sectionLength = (size_t) shdr64->sh_size;
	  sectionInImage = (void *) (image + shdr64->sh_offset);
	  sectionVirtualAddress = shdr64->sh_addr;
	}
	
	/* fprintf(stderr, "64bit ELF test info: sectionLength = %llu, image = %p, sectionInImage = %p, virtualAddress = %p\n", (unsigned long long) sectionLength, image, sectionInImage, (void*)sectionVirtualAddress); */
      }
      break;

    default:
      utilReturnWithMessage(0, "ELF object class of '%s' is %d - not supported - see elf.h", file, (int) elfClass);
      break;
  }


  if( NULL != shdr ) {

    if( 0 != copy ) {
      theCopy = malloc(sectionLength);
      
      if( NULL != theCopy ) {
	memcpy(theCopy, sectionInImage, sectionLength);
      }
    }
  }

  util_unmap_image(image, imageLength);

  if( NULL == shdr )
    utilReturnWithMessage(0, "can not locate ELF section '%s' in '%s'", sectionName, file);
 
  if( 0 != copy && NULL == theCopy )
    utilReturnWithMessage(0, "could not allocate memory (%llu bytes) for copy of ELF section '%s' in '%s'", (unsigned long long)sectionLength, sectionName, file);

  if( NULL != lengthPtr ) 
    *lengthPtr = sectionLength;  

  /* this cast allows casting void* to i.e. uint64_t regardless of platform void* width */
  return 0 != copy ? (LOGPOINT_ELF_ADDR) theCopy : sectionVirtualAddress;
}

/* the "elf-test"
main(int argc, char **argv)
{
  size_t length;
  Elf64_Addr section;

  if( NULL == argv[1] ) {
    fprintf(stderr, "Usage: %s <executable-with-logpoint-section>\n", argv[0]);
    return 1;
  }

  section = getSectionFromELFObject(argv[1], ".logpoints", 0, &length);
  
  printf("Virtual Logpoint section is at 0x%llx (%ld bytes)\n", section, length);

  section = getSectionFromELFObject(argv[1], ".logpoints", 1, &length);
  
  printf("Copied  Logpoint section is at 0x%llx (%ld bytes)\n", section, length);

  return 0;
}
*/


#endif
/* LOGPOINTS_USE_ELF */

#endif 
/* ER_EMBEDDED_NAME */

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

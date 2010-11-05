
/* catches self, needs a trick to return it cleanly */
/* not applicable because clang does not support builtin_apply */

void *logpoint_catchSelf(void *slf)
{
  fprintf(stderr, "slf: %p\n", slf);
  return slf;
}

void *logpoint_returnSelf(void *ret)
{
  fprintf(stderr, "ret2: %p\n", ret);
  __builtin_return(ret);
}

- (void) amethod
{
  void *args = __builtin_apply_args();

  fprintf(stderr, "self: %p\n", self);
  
  void *ret = __builtin_apply( (void (*)() ) logpoint_catchSelf, args, sizeof(void*) + sizeof(SEL));
  fprintf(stderr, "ret: %p\n", ret);
}

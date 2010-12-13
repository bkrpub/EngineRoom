#!/bin/bash

CFLAGS=""
#CFLAGS=" -Wno-unused-value"
#clang $CFLAGS -I../EngineRoom -I.. -x objective-c  -E t.c -framework Foundation > t.tmp

set -x
gcc $CFLAGS -I../EngineRoom -I.. -x objective-c  -o t t.c ../EngineRoom/logpoints.m  -framework Foundation ; ./t $@
clang $CFLAGS -I../EngineRoom -I.. -x objective-c  -o t t.c ../EngineRoom/logpoints.m  -framework Foundation ; ./t $@

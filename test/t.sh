#!/bin/bash

clang -Wno-unused-value -I../EngineRoom -I.. -x objective-c  -E t.c -framework Foundation > t.tmp
clang -Wno-unused-value -I../EngineRoom -I.. -x objective-c  -o t t.c ../EngineRoom/logpoints.m  -framework Foundation ; ./t

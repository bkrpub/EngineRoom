#!/bin/bash
set -e

name=$1

osx32="-arch i386 -arch ppc -framework Foundation -mmacosx-version-min=10.4 -isysroot /Developer/SDKs/MacOSX10.4u.sdk"
osx64="-arch x86_64 -arch ppc64 -framework Foundation -mmacosx-version-min=10.5 -isysroot /Developer/SDKs/MacOSX10.5.sdk"

set -x

mkdir -p tmp

gcc -ggdb $osx32 -o tmp/$name $name.m
gcc -ggdb $osx64 -o tmp/$name-64 $name.m
gcc  -fomit-frame-pointer -Os $osx32 -o tmp/$name-rel $name.m
#gcc  -fomit-frame-pointer -Os $osx64 -o tmp/$name-64-rel $name.m
gcc  -Os $osx64 -o tmp/$name-64-rel $name.m

set +x

echo debug 32
tmp/$name
echo debug 64
tmp/$name-64
echo release 32
tmp/$name-rel
echo release 64
tmp/$name-64-rel


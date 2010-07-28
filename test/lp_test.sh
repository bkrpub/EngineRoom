#!/bin/bash
set -e
set -x

mkdir -p tmp

[ -z "$LP_FILTER" ] && export LP_FILTER="setup,calc,visualize"

CSOURCES="lptest.c logpoints.c er_util.c"
CMSOURCES="lptest.c logpoints.m er_util.c"
MSOURCES="lptest.m logpoints.m er_util.c"

config='-DINTERNAL_WARNINGS'

if [ $(uname -s) = "Darwin" ] ; then
    CSOURCES="$CSOURCES tracer.c"
    CMSOURCES="$CMSOURCES tracer.m -framework Foundation"
    MSOURCES="$MSOURCES tracer.m -framework Foundation"
    
    gcc -Wall $config -ggdb -arch i386 -arch ppc -o tmp/lptest_c_32 $CSOURCES
    gcc -Wall $config -ggdb -arch i386 -arch ppc -o tmp/lptest_cm_32 $CMSOURCES
    gcc -Wall $config -ggdb -arch i386 -arch ppc -o tmp/lptest_m_32 $MSOURCES
    gcc -Wall $config -ggdb -arch x86_64 -arch ppc64 -o tmp/lptest_c_64 $CSOURCES
    gcc -Wall $config -ggdb -arch x86_64 -arch ppc64 -o tmp/lptest_cm_64 $CMSOURCES
    gcc -Wall $config -ggdb -arch x86_64 -arch ppc64 -o tmp/lptest_m_64 $MSOURCES
    tmp/lptest_c_32
    tmp/lptest_cm_32
    tmp/lptest_m_32
    tmp/lptest_c_64
    tmp/lptest_cm_64
    tmp/lptest_m_64
    
fi

if [ $(uname -s) = "Linux" ] ; then

    gcc -Wall $config -ggdb -m32 -o tmp/lptest_c_32 $CSOURCES
    gcc -Wall $config -ggdb -m64 -o tmp/lptest_c_64 $CSOURCES
    tmp/lptest_c_32
    tmp/lptest_c_64
fi

if [ $(uname -s) = "SunOS" ] ; then

    gcc -Wall $config -ggdb -m32 -o tmp/lptest_c_32 $CSOURCES
    gcc -Wall $config -ggdb -m64 -o tmp/lptest_c_64 $CSOURCES
    tmp/lptest_c_32
    tmp/lptest_c_64
fi


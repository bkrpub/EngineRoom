#!/bin/bash
set -e
set -x

stresstest="-framework AppKit -framework Quartz -framework QuartzCore -framework WebKit -framework ApplicationServices -framework CoreServices"

commonopt="-finstrument-functions -mmacosx-version-min=10.4"
# gcc 4.3: -finstrument-functions-exclude-file-list=/include

mkdir -p tmp
outfiles=""
for arch in i386 x86_64 ppc ppc64 ; do
    for opt in "-fno-omit-frame-pointer -O0" "-fomit-frame-pointer -Os" ; do
	out=$(echo "tmp/tracer_${arch}_$opt" | sed 's/-/_/g;s/ //g;')

	outc=${out}_c.out
	outm=${out}_m.out
	binc=${out}_c.bin
	binm=${out}_m.bin
	
	echo -n "testing $binc: "
	if { gcc -arch $arch $opt $commonopt -DTRACER_TEST -Wall -o $binc er_util.c tracer.c && ./$binc; } >$outc 2>&1 ; then 
	    echo DONE ; else echo FAIL ; fi
	outfiles="$outfiles $outc"
	echo -n "testing $binm: "
	if { gcc -arch $arch $opt $commonopt -DTRACER_TEST -Wall -o $binm er_util.c tracer.m -framework Foundation $stresstest && ./$binm ; } >$outm 2>&1 ; then
	    echo DONE ; else echo FAIL ; fi
	outfiles="$outfiles $outm"
    done
done

echo    
tar czf tmp/out.tar.gz $outfiles 
ls -l tmp/out.tar.gz

exit 0

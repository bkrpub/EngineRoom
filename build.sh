#!/bin/bash

VERSION="1.1.0"

CONFIGURATIONS="Release"
IOS_SDKS="iphoneos iphonesimulator"
IOS_VERSION="4.0"

set -e
set -x

BUILD_DIR="$(mktemp -d -t EngineRoom-build)"
[ -z "$BUILD_DIR" ] && echo 1>&2 "$0: could not create temporary build directory" && exit 1

options="BUILD_DIR=$BUILD_DIR"

for conf in $CONFIGURATIONS ; do 
    output="$BUILD_DIR/EngineRoom-$VERSION-$conf"
    mkdir -p "$output"
done


cd EngineRoom-OSX

product=EngineRoom.framework

for conf in $CONFIGURATIONS ; do 
    output="$BUILD_DIR/EngineRoom-$VERSION-$conf"

    xcodebuild $options -configuration $conf clean 
    xcodebuild $options -configuration $conf build
    mv "$BUILD_DIR/$conf/$product" "$output"
done

cd ..

cd EngineRoom-iOS

product=libEngineRoom.a

for conf in $CONFIGURATIONS ; do 
    output="$BUILD_DIR/EngineRoom-$VERSION-$conf"

    lipo_inputs=""
    for sdk in $IOS_SDKS ; do
	xcodebuild $options -sdk "$sdk$IOS_VERSION" -configuration $conf clean 
	xcodebuild $options -sdk "$sdk$IOS_VERSION" -configuration $conf build
	lipo_inputs="$lipo_inputs $BUILD_DIR/$conf-$sdk/$product"
    done

    mkdir "$output/lib"
    lipo -create $lipo_inputs -output "$output/lib/$product"
    cp -r "$BUILD_DIR/$conf-$sdk/include" "$output"
done

cd ..

echo "$BUILD_DIR"

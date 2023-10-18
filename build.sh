#!/bin/bash

BUILD_LOCATION=./dist/evex;

build() {
    echo "[INFO]: building to $BUILD_LOCATION"
    gcc -g evex.c util.c -o $BUILD_LOCATION
    echo "[INFO]: done."
}

clean() {
    echo "[INFO]: removing $BUILD_LOCATION"
    rm $BUILD_LOCATION
}

run() {
    shift
    $BUILD_LOCATION "$@"

    if [ $? -ne 0 ]; then
        echo "[ERROR]: execution of $BUILD_LOCATION failed."
        exit 1
    fi
}

if [ "$1" == "build" ]
then
    build
elif [ "$1" == "clean" ]
then
    clean
elif [ "$1" == "run" ]
then
    run $@
else
    echo "[ERROR]: Unsupported option."
    echo "[INFO]: Supported options: build, clean, run"

fi


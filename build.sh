#!/bin/bash

BUILD_LOCATION=dist/evex

if [ "$1" == "build" ]
then
     echo "[INFO]: building to $BUILD_LOCATION"
     gcc -g evex.c util.c -o $BUILD_LOCATION
     echo "[INFO]: done."

elif [ "$1" == "clean" ]
then
     echo "[INFO]: removing $BUILD_LOCATION"
     rm $BUILD_LOCATION

elif [ "$1" == "run" ]
then
    shift
    ./dist/evex "$@"

    if [ $? -ne 0 ]; then
        echo "[ERROR]: execution of $BUILD_LOCATION failed."
        exit 1
    fi

else
    echo "[ERROR]: Unsupported option."

fi


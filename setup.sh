#!/bin/bash

git submodule update --init --recursive

mkdir -p build
cd build

rm -f CMakeCache.txt

if [ "$#" -ne 1 ]; then
    cmake .. -G Unix\ Makefiles
    exit
fi

if [ $1 == "xcode" ]; then
    cmake .. -G Xcode
fi


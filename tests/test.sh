#!/bin/bash

mkdir -p  build
cd build
cmake ../.. -G Unix\ Makefiles
make

cd ..

build/voltz assemble test1-in out
cmp --silent out test1-out || echo "Test 1 Failed"

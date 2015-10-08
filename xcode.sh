#!/bin/bash

git submodule update --init
mkdir -p xcode
cd ./xcode

cmake .. -G Xcode
open ./voltz.xcodeproj

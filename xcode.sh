#!/bin/bash

git submodule init
mkdir -p xcode
cd ./xcode

cmake .. -G Xcode
open ./voltz.xcodeproj

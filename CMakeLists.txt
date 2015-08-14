project(voltz)
cmake_minimum_required(VERSION 2.8)

include_directories(include/)

add_library(voltz include/voltz.h src/voltz-internal.h src/voltz.cc)

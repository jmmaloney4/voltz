project(voltz)
cmake_minimum_required(VERSION 3.0)

include_directories(include/)

add_library(voltz include/voltz.h src/voltz-internal.h src/voltz.cc)

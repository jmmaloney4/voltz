project(voltz)
cmake_minimum_required(VERSION 3.0)

include_directories(include/)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")

add_library(voltz include/voltz.h src/voltz-internal.h src/voltz.cc src/int.cc src/float.cc)

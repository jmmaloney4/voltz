project(mach)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include/)
add_library(mach SHARED include/mach.h src/mach.cc src/mem.cc src/sel.cc src/object.cc)

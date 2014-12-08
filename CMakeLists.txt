project(mach)
cmake_minimum_required(VERSION 2.8)

include_directories(include/)
add_library(mach SHARED include/mach.h src/mach.cc)

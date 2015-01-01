project(mach)
cmake_minimum_required(VERSION 2.8)

add_subdirectory(deps/gtest)

include(CheckTypeSize)

CHECK_TYPE_SIZE("float" FLOAT_SIZE)
CHECK_TYPE_SIZE("double" DOUBLE_SIZE)
CHECK_TYPE_SIZE("signed char" CHAR_SIZE)
CHECK_TYPE_SIZE("signed short" SHORT_SIZE)
CHECK_TYPE_SIZE("signed int" INT_SIZE)
CHECK_TYPE_SIZE("signed long" LONG_SIZE)
CHECK_TYPE_SIZE("signed long long" LLONG_SIZE)

set(MACHRT_API_VERSION_MAJOR "0")
set(MACHRT_API_VERSION_MINOR "1")
set(MACHRT_API_VERSION_PATCH "0")
set(MACHRT_API_VERSION_TAG "")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c1x")

configure_file (
  "${PROJECT_SOURCE_DIR}/src/machrt/config.h.in"
  "${PROJECT_BINARY_DIR}/include/config.h"
  )

message("-- ${PROJECT_SOURCE_DIR}")

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/deps/gtest/include/")

add_library(machrt STATIC   src/machrt/config.h.in
                            src/machrt/machrt.h
                            src/machrt/machrt-private.h

                            src/machrt/machrt.c
                            src/machrt/load.c)

add_executable(mach_tests   src/test/main.cc)
target_link_libraries(mach_tests machrt gtest gtest_main)

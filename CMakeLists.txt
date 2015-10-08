project(voltz)
cmake_minimum_required(VERSION 2.8)

include_directories(include/)

option(test "Build all tests." ON)

if(APPLE)
    SET(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Deployment target for OSX" FORCE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif(APPLE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ferror-limit=0 -fdiagnostics-show-option -fdiagnostics-show-category=name -fdiagnostics-fixit-info")
endif()

set(CXX_FLAGS_TMP "${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x -pedantic -Weverything")

add_library(voltz include/voltz.h src/runtime/voltz-internal.h src/runtime/voltz.cc src/runtime/main.cc src/runtime/bootstrap.cc src/runtime/sel.cc src/runtime/number.cc src/runtime/message.cc src/runtime/imp.cc src/runtime/class.cc src/runtime/object.cc src/runtime/string.cc src/runtime/global.cc src/runtime/load.cc)

target_link_libraries(voltz dl)

add_library(std src/std/std.cc src/std/std.h src/std/bool.cc src/std/object.cc src/std/class.cc)

set(CMAKE_CXX_FLAGS "${CXX_FLAGS_TMP}")

if(test)

    include_directories(src/)

    add_subdirectory(lib/gtest)

    enable_testing()

    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    add_executable(tests test/test.cc)
    target_link_libraries(tests voltz std dl gtest gtest_main)

    add_test(NAME tests COMMAND tests)
endif()

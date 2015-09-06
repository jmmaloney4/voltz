project(voltz)
cmake_minimum_required(VERSION 2.8)

include_directories(include/)

option(test "Build all tests." ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")

add_library(voltz include/voltz.h src/runtime/voltz-internal.h src/runtime/voltz.cc src/runtime/main.cc src/runtime/bootstrap.cc src/runtime/sel.cc src/runtime/number.cc src/runtime/message.cc)

add_library(std src/std/std.cc src/std/io.cc)

if(test)
    add_subdirectory(lib/gtest)

    enable_testing()

    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    add_executable(tests test/test.cc)
    target_link_libraries(tests voltz gtest gtest_main)

    add_test(NAME tests COMMAND tests)
endif()

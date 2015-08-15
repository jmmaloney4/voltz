project(voltz)
cmake_minimum_required(VERSION 2.8)

include_directories(include/)

option(test "Build all tests." ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")

add_library(voltz include/voltz.h src/voltz-internal.h src/voltz.cc src/int.cc src/float.cc src/sel.cc src/string.cc src/registry.cc src/imp.cc)

if(test)
    add_subdirectory(lib/gtest)

    enable_testing()

    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    add_executable(tests test/test.cc)
    target_link_libraries(tests voltz gtest)

    add_test(NAME tests COMMAND tests)
endif()

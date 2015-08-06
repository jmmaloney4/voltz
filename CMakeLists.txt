project(voltz)
cmake_minimum_required(VERSION 2.8)

include_directories(include/)
add_executable(voltz include/voltz.h include/voltz-types.h include/voltz-bytecode.h src/main.cc src/bytecode.cc src/assembly.cc src/binary.cc src/registry.cc src/runtime.cc src/selector.cc)

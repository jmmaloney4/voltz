project(voltz)
cmake_minimum_required(VERSION 2.8)

include_directories(include/)
add_executable(voltz include/voltz.h include/voltz-types.h include/voltz-bytecode.h src/bytecode.cc src/assembly.cc src/main.cc)

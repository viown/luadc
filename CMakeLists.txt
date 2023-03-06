cmake_minimum_required(VERSION 3.25)

project(luadc)

set(CMAKE_CXX_FLAGS "-m32")

add_executable(luadc.out luadc/disassemble.cpp luadc/luadc.cpp)
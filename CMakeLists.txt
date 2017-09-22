cmake_minimum_required(VERSION 2.8.9)
project (MYCPPMATH)

#compiler
#set(CMAKE_C_COMPILER C:/"Program Files (x86)"/GCC/bin/gcc.exe)
set(CMAKE_C_COMPILER gcc)

#set(CMAKE_CXX_COMPILER C:/"Program Files (x86)"/GCC/bin/g++.exe)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -c")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2 -m64 -march=native")
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2 -m32 -march=native")

#header
include_directories(../include)

#cpp
set(SRC ../src/mycppmath.cpp ../test/test.cpp)

add_executable(MYCPPMATH ${SRC})
cmake_minimum_required(VERSION 3.14)
project(GA)

set(CMAKE_CXX_STANDARD 14)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

set(SOURCE_FILES main.cpp)

add_executable(GA main.cpp)
cmake_minimum_required(VERSION 2.8.2)

project(graph_lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -O3")

file(GLOB srcs *.cpp)

add_library(graph STATIC ${srcs})

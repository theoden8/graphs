cmake_minimum_required(VERSION 2.8.2)

include_directories(
	${GRAPH_LIB}
	${GTEST_LIB}
	${GMOCK_LIB}
)

project(graph_test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g3")

file(GLOB srcs *.cpp)

add_executable(_tgraph ${srcs})
target_link_libraries(_tgraph libgtest libgmock graph)

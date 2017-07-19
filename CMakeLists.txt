cmake_minimum_required(VERSION 2.8.2)

project(graph)

set(DIRROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(DIRINCLUDE ${DIRROOT}/include)

MESSAGE( STATUS "DIRROOT:     " ${DIRROOT})
MESSAGE( STATUS "DIRINCLUDE:  " ${DIRINCLUDE})

add_compile_options(-std=c++1z)

# ------------- EXTERNAL LIBRARIES --------------

# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
	gtest
	URL https://github.com/google/googletest/archive/release-1.8.0.zip
	PREFIX ${DIRINCLUDE}/gtest
	# Disable install step
	INSTALL_COMMAND ""
)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set gtest properties
ExternalProject_Get_Property(gtest source_dir binary_dir)
set_target_properties(libgtest PROPERTIES
	IMPORTED_LOCATION "${binary_dir}/googlemock/gtest/libgtest.a"
	IMPORTED_LINK_INTERFACE_LIBRARIES "${CMAKE_THREAD_LIBS_INIT}"
)
set(GTEST_LIB "${source_dir}/googletest/include")

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gmock)

# Set gmock properties
set_target_properties(libgmock PROPERTIES
	"IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
#	"INTERFACE_INCLUDE_DIRECTORIES" "${source_dir}/include"
)
# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
set(GMOCK_LIB "${source_dir}/googlemock/include")

# ----------------- GRAPH_LIB -------------------

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DIRROOT}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DIRINCLUDE})

set(GRAPH_LIB ${DIRROOT}/lib)
set(GRAPH_TEST ${DIRROOT}/test)

add_subdirectory(${GRAPH_LIB})
add_subdirectory(${GRAPH_TEST})

# ----------------- TESTING -----------------

enable_testing()

add_test(Graphs ./bin/_tgraph)

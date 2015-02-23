cmake_minimum_required(VERSION 2.8)

project (ACGE)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/external)

option(BUILD_TESTS "Build Tests" ON)
option(BUILD_EXAMPLES "Build Tests" ON)

set(ACGE_BINARY_DIR "${CMAKE_BINARY_DIR}/bin")
set(ACGE_TESTS_DIR "${CMAKE_BINARY_DIR}/bin/tests")
set(ACGE_EXAMPLES_DIR "${CMAKE_BINARY_DIR}/bin/examples")

if(BUILD_TESTS)
	add_subdirectory(tests)
endif(BUILD_TESTS)

if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif(BUILD_EXAMPLES)

add_subdirectory(src acge)

make_directory(bin)
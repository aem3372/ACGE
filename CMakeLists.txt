cmake_minimum_required(VERSION 2.8)

project (ACGE)

if(WIN32)
	set(PLATFORM_FOLDER win32)
endif(WIN32)

include_directories(${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/external
	${PROJECT_SOURCE_DIR}/external/freeimage/include/${PLATFORM_FOLDER}
	${PROJECT_SOURCE_DIR}/external/opengl/glew-1.9.0/include
	${PROJECT_SOURCE_DIR}/external/opengl/glfw-3.0.3/include
	${PROJECT_SOURCE_DIR}/external/opengl/glm-0.9.4.0)

option(BUILD_TESTS "Build Tests" ON)
option(BUILD_EXAMPLES "Build Tests" ON)

set(ACGE_ROOT ${PROJECT_SOURCE_DIR})

set(ACGE_BINARY_DIR ${CMAKE_BINARY_DIR}/bin)
set(ACGE_EXTERNAL_DIR ${CMAKE_BINARY_DIR}/bin/external)
set(ACGE_TESTS_DIR ${CMAKE_BINARY_DIR}/bin/tests)
set(ACGE_EXAMPLES_DIR ${CMAKE_BINARY_DIR}/bin/examples)



if(BUILD_TESTS)
	add_subdirectory(tests)
endif(BUILD_TESTS)

if(BUILD_EXAMPLES)
	add_subdirectory(examples)
endif(BUILD_EXAMPLES)

add_subdirectory(src acge)

add_subdirectory(external)

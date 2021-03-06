# BUILD_SHARED_LIBS is a standard CMake variable, but we declare it here to
# make it prominent in the GUI.
#option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." OFF)

# When other libraries are using a shared version of runtime libraries,
#option(
#  gtest_force_shared_crt
#  "Use shared (DLL) run-time lib even when Google Test is built as static lib."
#  OFF)
set(gtest_force_shared_crt ON)

#option(gtest_build_tests "Build all of gtest's own tests." OFF)

#option(gtest_build_samples "Build gtest's sample programs." OFF)

#option(gtest_disable_pthreads "Disable uses of pthreads in gtest." OFF)

# Defines pre_project_set_up_hermetic_build() and set_up_hermetic_build().
include(cmake/hermetic_build.cmake OPTIONAL)

if (COMMAND pre_project_set_up_hermetic_build)
  pre_project_set_up_hermetic_build()
endif()

########################################################################
#
# Project-wide settings

# CMake files in this project can refer to the root source directory
# as ${gtest_SOURCE_DIR} and to the root binary directory as
# ${gtest_BINARY_DIR}.
# Language "C" is required for find_package(Threads).

project(gtest CXX C)

if (COMMAND set_up_hermetic_build)
  set_up_hermetic_build()
endif()

# Define helper functions and macros used by Google Test.
include(cmake/internal_utils.cmake)

config_compiler_and_linker()  # Defined in internal_utils.cmake.

# Where Google Test's .h files can be found.
include_directories(
  ${gtest_SOURCE_DIR}/include
  ${gtest_SOURCE_DIR})

# Where Google Test's libraries can be found.
link_directories(${gtest_BINARY_DIR}/src)

########################################################################
#
# Defines the gtest & gtest_main libraries.  User tests should link
# with one of them.

# Google Test libraries.  We build them using more strict warnings than what
# are used for other targets, to ensure that gtest can be compiled by a user
# aggressive about warnings.
cxx_library(gtest "${cxx_strict}" src/gtest-all.cc)
cxx_library(gtest_main "${cxx_strict}" src/gtest_main.cc)
target_link_libraries(gtest_main gtest)

set_target_properties(gtest
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ACGE_EXTERNAL_DIR}/gtest"
    ARCHIVE_OUTPUT_DIRECTORY "${ACGE_EXTERNAL_DIR}/gtest"
    LIBRARY_OUTPUT_DIRECTORY "${ACGE_EXTERNAL_DIR}/gtest"
)

set_target_properties(gtest_main
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ACGE_EXTERNAL_DIR}/gtest"
    ARCHIVE_OUTPUT_DIRECTORY "${ACGE_EXTERNAL_DIR}/gtest"
    LIBRARY_OUTPUT_DIRECTORY "${ACGE_EXTERNAL_DIR}/gtest"
)

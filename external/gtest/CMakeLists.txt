########################################################################
# Google Test.(ACGE reconfig)
#

set(GTEST_SOURCE_DIR ./)

# Where Google Test's .h files can be found.

set(GTEST_INCLUDE 
  ${GTEST_SOURCE_DIR}/include
  ${GTEST_SOURCE_DIR})

include_directories(${GTEST_INCLUDE})

########################################################################
#
# Defines the gtest & gtest_main libraries.  User tests should link
# with one of them.

# Google Test libraries.  We build them using more strict warnings than what
# are used for other targets, to ensure that gtest can be compiled by a user
# aggressive about warnings.
add_library(gtest src/gtest-all.cc)
add_library(gtest_main src/gtest_main.cc)
target_link_libraries(gtest_main gtest)

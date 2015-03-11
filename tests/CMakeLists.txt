include_directories(${ACGE_ROOT}/external/gtest/include)

include(device/CMakeLists.txt)
include(math/CMakeLists.txt)
include(platform/CMakeLists.txt)

add_executable(unit_tests
	${ACGE_TEST_DEVICE_SRC}
	${ACGE_TEST_MATH_SRC}
	${ACGE_TEST_PLATFORM_SRC}
)

target_link_libraries(unit_tests acge gtest_main)

set_target_properties(unit_tests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ACGE_TESTS_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${ACGE_TESTS_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${ACGE_TESTS_DIR}"
)

include(resource/CMakeLists.txt)
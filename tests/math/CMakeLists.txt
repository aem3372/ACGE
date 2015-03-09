add_executable(test_point_transformator test_point_transformator.cpp)

target_link_libraries(test_point_transformator acge gtest_main)

set_target_properties(test_point_transformator
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ACGE_TESTS_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${ACGE_TESTS_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${ACGE_TESTS_DIR}"
)

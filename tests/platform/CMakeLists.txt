add_executable(test_dynamic_linker test_dynamic_linker.cpp)
add_executable(test_text_log test_text_log.cpp)

target_link_libraries(test_dynamic_linker acge)
target_link_libraries(test_text_log acge)

set_target_properties(test_dynamic_linker
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ACGE_TESTS_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${ACGE_TESTS_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${ACGE_TESTS_DIR}"
)

set_target_properties(test_text_log
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ACGE_TESTS_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${ACGE_TESTS_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${ACGE_TESTS_DIR}"
)
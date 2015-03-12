add_library(mock_object SHARED mock_object.cpp)

set_target_properties(mock_object
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ACGE_TESTS_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${ACGE_TESTS_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${ACGE_TESTS_DIR}"
)

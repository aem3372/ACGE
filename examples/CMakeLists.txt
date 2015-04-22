add_executable(example1 example1.cpp)

target_link_libraries(example1 acge)

set_target_properties(example1
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
)

INSTALL(TARGETS	example1
    RUNTIME DESTINATION bin)
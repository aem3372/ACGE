include(device/CMakeLists.txt)
include(math/CMakeLists.txt)
include(platform/CMakeLists.txt)

add_library(acge STATIC
	${ACGE_DEVICE_SRC}
	${ACGE_MATH_SRC}
	${ACGE_PLATFORM_SRC}
)

set_target_properties(acge
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
)
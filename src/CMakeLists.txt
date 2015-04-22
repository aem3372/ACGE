include(device/CMakeLists.txt)
include(math/CMakeLists.txt)
include(tools/CMakeLists.txt)
include(render/CMakeLists.txt)

set(PNG_LIB ${ACGE_ROOT}/external/freeimage/lib/${PLATFORM_FOLDER}/freeimage.lib)

add_library(acge STATIC
	${ACGE_DEVICE_SRC}
	${ACGE_MATH_SRC}
	${ACGE_PLATFORM_SRC}
	${ACGE_TOOLS_SRC}
	${ACGE_RENDER_SRC}
)

target_link_libraries(acge
	${PNG_LIB}
)

set_target_properties(acge
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
)

INSTALL(TARGETS
		acge
	LIBRARY DESTINATION 
		lib
	ARCHIVE DESTINATION 
		lib)
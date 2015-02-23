set(ACGE_DEVICE_OPENGL_SRC
	graphics_device.cpp
)

add_library(device_opengl SHARED
	${ACGE_DEVICE_OPENGL_SRC}
)

target_link_libraries(device_opengl 	${PROJECT_SOURCE_DIR}/external/opengl/opengl.lib
	${PROJECT_SOURCE_DIR}/external/opengl/glut.lib
	${PROJECT_SOURCE_DIR}/external/opengl/glu.lib
)

set_target_properties(device_opengl
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
)
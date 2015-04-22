find_package(OpenGL REQUIRED)

add_definitions(
	-DDLL_EXPORT
)

set(ACGE_DEVICE_OPENGL_SRC
	GraphicsDevice.cpp
)

add_library(device_opengl SHARED
	${ACGE_DEVICE_OPENGL_SRC}
)

target_link_libraries(device_opengl 	
	${OPENGL_LIBRARY}
	GLEW_190
	GLFW_303
)

set_target_properties(device_opengl
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
)

INSTALL(TARGETS	device_opengl
    LIBRARY DESTINATION bin
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib)
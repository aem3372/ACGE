set(ACGE_DEVICE_GDIPLUS_SRC
	graphics_device.cpp
)

add_library(device_gdiplus SHARED
	${ACGE_DEVICE_GDIPLUS_SRC}
)

target_link_libraries(device_gdiplus 	${PROJECT_SOURCE_DIR}/external/GDIPlus/Lib/GdiPlus.lib
)

set_target_properties(device_gdiplus
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${ACGE_BINARY_DIR}"
)
#add_subdirectory(device/gdiplus)
add_subdirectory(device/opengl)

set(ACGE_DEVICE_SRC
	device/Device.h
	device/GraphicsDeviceFactory.h
	device/GraphicsDeviceStruct.h
	device/IGraphicsDevice.h

	device/GraphicsDeviceFactory.cpp
)
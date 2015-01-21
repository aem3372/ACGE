@echo off
set LD_LIBRARY_PATH=./
set CPLUS_INCLUDE_PATH=../src;../external;

echo Make:单元测试组件  测试对象:point transformator
g++ ../test/unittest/math/test_point_transformator.cpp -o test_point_transformator.exe

echo Make:单元测试组件  测试对象:gdiplus device
g++ ../src/device/gdiplus/graphics_device.cpp ../external/GDIPlus/Lib/GdiPlus.lib --share -o libdevice-gdiplus.dll
g++ ../test/unittest/device/gdiplus/test_gdiplus_device.cpp libdevice-gdiplus.dll -o test_gdiplus_device.exe

echo Make:单元测试组件  测试对象:opengl device
g++ ../src/device/opengl/graphics_device.cpp ../external/opengl/opengl.lib ../external/opengl/glut.lib ../external/opengl/glu.lib --share -o libdevice-opengl.dll
g++ ../test/unittest/device/opengl/test_opengl_device.cpp libdevice-opengl.dll -o test_opengl_device.exe

echo Make:单元测试组件  测试对象:dynamic linker
g++ -c ../src/platform/dynamic_linker.cpp -o dynamic_linker.o
g++ ../test/unittest/platform/test_dynamic_linker.cpp dynamic_linker.o -o test_dynamic_linker.exe

echo Make:单元测试组件  测试对象:text log
g++ -c ../src/platform/text_log.cpp -o text_log.o
g++ ../test/unittest/platform/test_text_log.cpp text_log.o -o test_text_log.exe

echo Make:单元测试组件  测试对象:graphics device factory
g++ -c ../src/device/graphics_device_factory.cpp -o graphics_device_factory.o
g++ ../test/unittest/device/test_graphics_device_factory.cpp graphics_device_factory.o dynamic_linker.o -o test_graphics_device_factory.exe

pause

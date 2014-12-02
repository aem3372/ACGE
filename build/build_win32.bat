set LD_LIBRARY_PATH=./
set CPLUS_INCLUDE_PATH=../src
g++ ../src/device/gdiplus/graphics_device.cpp ../external/GDIPlus/Lib/GdiPlus.lib --share -o libdevice-gdiplus.dll
g++ ../test/unittest/device/gdiplus/test_gdiplus_device.cpp libdevice-gdiplus.dll -o test_gdiplus_device.exe -g
test_gdiplus_device.exe
pause
#include <cstdio>
#include <cstdlib>
#include "platform/dynamic_linker.h"
#include "device/gdiplus/graphics_device.h"

int main() 
{
    DynamicLinker* linker = DynamicLinker::getInstance();
    linker->loadLibrary("device-gdiplus","C:\\dev\\ACGE\\build\\libdevice-gdiplus.dll");
    linker->getProcAddress("device-gdiplus","createInstance");
    linker->freeLibrary("device-gdiplus");
    return 0;
}
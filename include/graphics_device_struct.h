#ifndef __ACGE_GRAPHICS_DEVEICE_STRUCT__
#define __ACGE_GRAPHICS_DEVEICE_STRUCT__

#include "platform.h"

struct GraphicsDeviceInfo
{
    long xres;
    long yres;
    int depth;
};

#ifdef _ACGE_PLATFORM_WIN32

struct GraphicsContext
{
    HWND hwnd;
};

#endif

#ifdef _ACGE_PLATFORM_LINUX

struct GraphicsContext
{
    int fb;
};

#endif


#endif
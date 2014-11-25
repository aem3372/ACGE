#ifndef __ACGE_GRAPHICS_DEVEICE_INTERFACE__
#define __ACGE_GRAPHICS_DEVEICE_INTERFACE__

#include "graphics_device_struct.h"
#include "i_unknow.h"

class IGraphicsDevice
: public IUnknow
{
    virtual GraphicsDeviceInfo getDeviceInfo() = 0;
};

#endif

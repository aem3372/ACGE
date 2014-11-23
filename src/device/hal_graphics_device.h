#ifndef __ACGE_HAL_GRAPHICS_DEVICE__
#define __ACGE_HAL_GRAPHICS_DEVICE__

#include "i_graphics_device.h"

class HALGraphicsDevice
{
public:
    bool init(IGraphicsDevice* device);
    void drawPoint(int x, int y);
private:
    IGraphicsDevice* device;
};

#endif
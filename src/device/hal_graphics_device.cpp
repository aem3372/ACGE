#include <cstdlib>
#include "hal_graphics_device.h"

bool HALGraphicsDevice::init(IGraphicsDevice* device)
{
    this->device = device;
}

void HALGraphicsDevice::drawPoint(int x, int y)
{
    IDrawPoint* pd = device->query("IDrawPoint");
    if(pd)
        pd->drawPoint(x, y);
    else
        exit(80);
}
#include <cstring>
#include "graphice_device.h"

IUnkonw* GraphiceDevice::query(char* unknow)
{
    if(!std::strcmp(unknow, "IDrawPoint"))
    {
        return static_cast<IDrawPoint*>(device);
    }
    else if(!std::strcmp(unknow, "IGraphicsDevice"))
    {
        return static_cast<IGraphicsDevice*>(device);
    }
    else
    {
        return NULL;
    }
}

void GraphiceDevice::drawPoint(int x, int y)
{
    
}
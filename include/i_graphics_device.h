#ifndef __ACGE_GRAPHICS_DEVEICE_INTERFACE__
#define __ACGE_GRAPHICS_DEVEICE_INTERFACE__

#include "graphics_device_struct.h"

class IGraphicsDevice
{
public:
    virtual void initGraphics(GraphicsContext* context) = 0;
    virtual GraphicsDeviceInfo getDeviceInfo() = 0;
    virtual void drawBegin() = 0;
    virtual void drawEnd() = 0;
    virtual void drawPoint(int x, int y) = 0;
    virtual void drawLine(int x1, int y1, int x2, int y2) = 0;
    virtual void setColor(float a, float r, float g, float b) = 0;
    virtual void clearSufface() = 0;
    virtual void destory() = 0;
};

#endif

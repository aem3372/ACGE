#include "device/framebuffer/graphics_device.h"

int main()
{
    GraphicsDevice* device = new GraphicsDevice();
    device->setARGBColor(0xFFFF0000);
    device->drawPoint(100,100);
    device->release();
    return 0;
}
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include "device/framebuffer/graphics_device.h"
#include "device/graphics_device_struct.h"
#include "device/i_graphics_device.h"
#include "device/i_graphics_drawpoint.h"
#include "device/i_graphics_argbcolor.h"
#include "device/i_graphics_clearsufface.h"

int main()
{
    int fp = open("/dev/fb0",O_RDWR);
    
    if(fp < 0)
    {
        std::printf("Error: Can not open framebuffer device\n");
        std::exit(1);
    }

    IUnknow* pInstance = createInstance(fp);

    IARGBColor* pARGBColor;
    if(pInstance->queryInterface("IARGBColor", (void**)&pARGBColor))
    {
        pARGBColor->setARGBColor(0x00FFFFFF);
        pARGBColor->release();
    }
    else
    {
        printf("queryInterface: IARGBColor  failed!\n");
    }
    IGraphicsDevice* pGraphicsDevice;
    GraphicsDeviceInfo info;
    if(pInstance->queryInterface("IGraphicsDevice", (void**)&pGraphicsDevice))
    {
        info = pGraphicsDevice->getDeviceInfo();
        pGraphicsDevice->release();
    }
    else
    {
        printf("queryInterface: IGraphicsDevice  failed!\n");
    }
    
    IClearSufface* pClearSufface;
    IDrawPoint* pDrawPoint;
    if(!pInstance->queryInterface("IClearSufface", (void**)&pClearSufface))
    {
        printf("queryInterface: IClearSufface  failed!\n");
    }
    if(!pInstance->queryInterface("IDrawPoint", (void**)&pDrawPoint))
    {
        printf("queryInterface: IDrawPoint  failed!\n");
    }

    int x = 0, y = 400; 
    int dx = 1;
    while(1)
    {
        pClearSufface->clearSufface();
        
        pDrawPoint->drawPoint(x ,y);
        
        if(x+dx >= info.xres || x+dx < 0)
        {
            dx = -dx;
        }

        //x += dx;
        
        usleep(1000);
    }
    if(pClearSufface)
        pClearSufface->release();
    if(pDrawPoint)
        pDrawPoint->release();
    pInstance->release();
    return 0;
}

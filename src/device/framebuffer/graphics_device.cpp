#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "graphics_device.h"

GraphicsDevice::GraphicsDevice()
    : reference(1)
    , color(0xFFFFFFFF)
{
    fp = open("/dev/fb0",O_RDWR);
    
    if(fp < 0)
    {
        printf("Error: Can not open framebuffer device\n");
        exit(1);
    }

    if(ioctl(fp,FBIOGET_FSCREENINFO,&finfo))
    {
        printf("Error reading fixed information\n");
        exit(2);
    }

    if(ioctl(fp, FBIOGET_VSCREENINFO, &vinfo))
    {
        printf("Error reading variable information\n");
        exit(3);
    }
    
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel/8;
    fbp = (char*)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fp, 0);
    printf("fbp: %p\n", fbp);
}

GraphicsDevice::~GraphicsDevice()
{
    munmap(fbp, screensize);
    close(fp);
}

void GraphicsDevice::retain()
{
    ++reference;
}

void GraphicsDevice::release()
{
    --reference;
    if(!reference)
    {
        delete this;
    }
}


int GraphicsDevice::queryInterface(char* unknow, void** pp)
{
    if(!std::strcmp(unknow, "IDrawPoint"))
    {
        *pp = static_cast<IDrawPoint*>(this);
        return 1;
    }
    else if(!std::strcmp(unknow, "IGraphicsDevice"))
    {
        *pp = static_cast<IGraphicsDevice*>(this);
        return 1;
    }
    else
    {
        *pp = NULL;
        return 0;
    }
}

void GraphicsDevice::drawPoint(int x, int y)
{
    long location = x * (vinfo.bits_per_pixel / 8) + y * finfo.line_length;
    char* p = fbp + location;
    *p++ = color & 0xFF; //B
    *p++ = (color >> 8) & 0xFF; //G
    *p++ = (color >> 16)& 0xFF; //R
    *p++ = (color >> 24)& 0xFF;  //A
}

void GraphicsDevice::setARGBColor(unsigned long argb)
{
    color = argb;
}

unsigned long GraphicsDevice::getARGBColor()
{
    return color;
}

GraphicsDeviceInfo GraphicsDevice::getDeviceInfo()
{
    GraphicsDeviceInfo info;
    return info;
}
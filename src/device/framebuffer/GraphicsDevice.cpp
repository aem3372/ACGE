#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include "../i_graphics_device.h"
#include "../i_graphics_drawpoint.h"
#include "../i_graphics_argbcolor.h"
#include "../i_graphics_clearsufface.h"
#include "../graphics_device_struct.h"
#include "platform/text_log.h"

class GraphicsDevice
: public IDrawPoint
, public IARGBColor
, public IGraphicsDevice
, public IClearSufface
{
public:
    GraphicsDevice(int fb);
    ~GraphicsDevice();

    virtual void retain();
    virtual void release();
    virtual int queryInterface(const char* unknow, void** pp);
    virtual void drawPoint(int x, int y);
    virtual void setARGBColor(unsigned long argb);
    virtual unsigned long getARGBColor();
    virtual void clearSufface();
    virtual GraphicsDeviceInfo getDeviceInfo();

private:
    int reference;
    int fp;
    char* fbp;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    int screensize;
    unsigned long color;
};

#include "graphics_device.h"

GraphicsDevice::GraphicsDevice(int fb)
    : reference(1)
    , color(0x00FFFFFF)
{
    fp = fb;

    if(fp < 0)
    {
        TextLog::error(0,"Error: Can not open framebuffer device\n");
        exit(1);
    }

    if(ioctl(fp,FBIOGET_FSCREENINFO,&finfo))
    {
        TextLog::error(0,"Error reading fixed information\n");
        exit(2);
    }

    if(ioctl(fp, FBIOGET_VSCREENINFO, &vinfo))
    {
        TextLog::error(0,"Error reading variable information\n");
        exit(3);
    }
    
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel/8;
    fbp = (char*)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fp, 0);
}

GraphicsDevice::~GraphicsDevice()
{
    munmap(fbp, screensize);
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


int GraphicsDevice::queryInterface(const char* unknow, void** pp)
{
    if(!std::strcmp(unknow, "IDrawPoint"))
    {
        *pp = static_cast<IDrawPoint*>(this);
    }
    else if(!std::strcmp(unknow, "IGraphicsDevice"))
    {
        *pp = static_cast<IGraphicsDevice*>(this);
    }
    else if(!std::strcmp(unknow, "IARGBColor"))
    {
        *pp = static_cast<IARGBColor*>(this);
    }
    else if(!std::strcmp(unknow, "IClearSufface"))
    {
        *pp = static_cast<IClearSufface*>(this);
    }
    else
    {
        *pp = NULL;
    }
    
    if(*pp)
    {
        this->retain();
        return 1;
    }
    else
    {
        return 0;
    }
}

void GraphicsDevice::drawPoint(int x, int y)
{
    long location = (y * vinfo.xres + x) * (vinfo.bits_per_pixel / 8);
    *(fbp + location) = color & 0xFF; //B
    *(fbp + location + 1) = (color >> 8) & 0xFF; //G
    *(fbp + location + 2) = (color >> 16)& 0xFF; //R
    *(fbp + location + 3) = (color >> 24)& 0xFF; //A
}

void GraphicsDevice::setARGBColor(unsigned long argb)
{
    color = argb;
}

unsigned long GraphicsDevice::getARGBColor()
{
    return color;
}

void GraphicsDevice::clearSufface()
{
    memset(fbp, 0x00, (vinfo.xres * vinfo.yres) * (vinfo.bits_per_pixel / 8));
}

GraphicsDeviceInfo GraphicsDevice::getDeviceInfo()
{
    GraphicsDeviceInfo info;
    info.xres = vinfo.xres;
    info.yres = vinfo.yres;
    info.depth = vinfo.bits_per_pixel;
    return info;
}


IUnknow* createInstance(int fb)
{
    return static_cast<IGraphicsDevice*>(new GraphicsDevice(fb));
}
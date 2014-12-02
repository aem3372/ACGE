#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define ULONG_PTR ULONG
#include <gdiplus.h>//gdi+头文件

#include "../i_graphics_device.h"
#include "../i_graphics_drawpoint.h"
#include "../i_graphics_argbcolor.h"
#include "../i_graphics_clearsufface.h"
#include "../graphics_device_struct.h"

using namespace Gdiplus;

class GraphicsDevice
: public IDrawPoint
, public IARGBColor
, public IGraphicsDevice
, public IClearSufface
{
public:
    GraphicsDevice(HWND hwnd);
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
    HWND hwnd;
    HDC hdc;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR pGdiToken;
    Graphics *graphics;
    unsigned long color;
};

#include "graphics_device.h"

GraphicsDevice::GraphicsDevice(HWND hWnd)
    : reference(1)
    , color(0x00FFFFFF)
{
    GdiplusStartup(&pGdiToken,&gdiplusStartupInput,NULL);//初始化GDI+
    
    hwnd = hWnd;
    hdc = GetDC(hwnd);
    graphics = Graphics::FromHDC(hdc);
}

GraphicsDevice::~GraphicsDevice()
{
    if(hdc)
        ReleaseDC(hwnd,hdc);
    if(graphics)
        delete graphics;
    GdiplusShutdown(pGdiToken);//关闭GDI+
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
    if(!strcmp(unknow, "IDrawPoint"))
    {
        *pp = static_cast<IDrawPoint*>(this);
    }
    else if(!strcmp(unknow, "IGraphicsDevice"))
    {
        *pp = static_cast<IGraphicsDevice*>(this);
    }
    else if(!strcmp(unknow, "IARGBColor"))
    {
        *pp = static_cast<IARGBColor*>(this);
    }
    else if(!strcmp(unknow, "IClearSufface"))
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
    Pen pen(Color(255, 255, 0, 0));
    graphics->DrawRectangle(&pen, x, y, 1, 1);
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
    Color blackColor(255, 0, 0, 0);
    graphics->Clear(blackColor);
}

GraphicsDeviceInfo GraphicsDevice::getDeviceInfo()
{
    GraphicsDeviceInfo info;
    RECT lpRect;  
    GetClientRect(hwnd, &lpRect);  
    int hight = lpRect.bottom - lpRect.top;  
    int width = lpRect.right - lpRect.left;  
    info.xres = width;
    info.yres = hight;
    info.depth = 0;
    return info;
}

IUnknow* createInstance(HWND hwnd)
{
    return static_cast<IGraphicsDevice*>(new GraphicsDevice(hwnd));
}
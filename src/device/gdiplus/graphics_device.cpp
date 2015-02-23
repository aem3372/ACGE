#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define ULONG_PTR ULONG
#include <gdiplus.h>//gdi+头文件

#include "../i_graphics_device.h"
#include "../graphics_device_struct.h"
#include "point_transformator.h"
#include "platform/text_log.h"

using namespace Gdiplus;

class GraphicsDevice
: public IGraphicsDevice
{
public:
    GraphicsDevice();
    ~GraphicsDevice();

    virtual void initGraphics(GraphicsContext* context);
    virtual GraphicsDeviceInfo getDeviceInfo();
    virtual void drawBegin();
    virtual void drawEnd();
    virtual void drawPoint(int x, int y);
    virtual void drawLine(int x1, int y1, int x2, int y2);
    virtual void setColor(float a, float r, float g, float b);
    virtual void clearSufface();
    virtual void destory();

private:
    HWND hwnd;
    HDC hdc;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR pGdiToken;
    Graphics *graphics;
    Bitmap *bitmap;
    Graphics *bitmapGraphics;
    Pen *pen;
    PointTransformator<int> trans;
    int hight;
    int width;
};

#include "graphics_device.h"

GraphicsDevice::GraphicsDevice()
{

}

GraphicsDevice::~GraphicsDevice()
{
    if(hdc)
        ReleaseDC(hwnd,hdc);
    if(pen)
        delete pen;
    if(graphics)
        delete graphics;
    if(pGdiToken)
        GdiplusShutdown(pGdiToken);//关闭GDI+
}

void GraphicsDevice::drawPoint(int x, int y)
{
    trans.LT2LB(x,y,&x,&y);
    bitmapGraphics->DrawRectangle(pen, x, y, 1, 1);
}

void GraphicsDevice::drawLine(int x1, int y1, int x2, int y2)
{
    trans.LT2LB(x1,y1,&x1,&y1);
    trans.LT2LB(x2,y2,&x2,&y2);
    bitmapGraphics->DrawLine(pen,x1,y1,x2,y2);
}

void GraphicsDevice::setColor(float a, float r, float g, float b)
{
	unsigned char ua = (unsigned char)a * 0xFF;
	unsigned char ur = (unsigned char)r * 0xFF;
	unsigned char ug = (unsigned char)g * 0xFF;
	unsigned char ub = (unsigned char)b * 0xFF;
    Color gdiplusColor(ua, ur, ug, ub);
    pen->SetColor(gdiplusColor);
}

void GraphicsDevice::clearSufface()
{
    Color blackColor(0xFF, 0, 0, 0);
    bitmapGraphics->Clear(blackColor);
}

GraphicsDeviceInfo GraphicsDevice::getDeviceInfo()
{
    GraphicsDeviceInfo info;
    RECT lpRect;  
    GetClientRect(hwnd, &lpRect);  
    hight = lpRect.bottom - lpRect.top;  
    width = lpRect.right - lpRect.left;  
    info.xres = width;
    info.yres = hight;
    info.depth = 0;
    return info;
}

void GraphicsDevice::initGraphics(GraphicsContext* context)
{
    GdiplusStartup(&pGdiToken,&gdiplusStartupInput,NULL);//初始化GDI+
    hwnd = context->hwnd;
    hdc = ::GetDC(hwnd);
    graphics = Graphics::FromHDC(hdc);

    RECT lpRect;  
    GetClientRect(hwnd, &lpRect);  
    int hight = lpRect.bottom - lpRect.top;  
    int width = lpRect.right - lpRect.left;  
    trans.init(width, hight);

    pen = new Pen(Color(0xFF, 0xFF, 0xFF, 0xFF));
    bitmap = new Bitmap(width, hight);
}

void GraphicsDevice::drawBegin()
{
    bitmapGraphics = Graphics::FromImage(bitmap);
}

void GraphicsDevice::drawEnd()
{
    graphics->DrawImage(bitmap, 0,0,width,hight);
}

void GraphicsDevice::destory()
{
    delete this;
}

IGraphicsDevice* createInstance()
{
    return static_cast<IGraphicsDevice*>(new GraphicsDevice());
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


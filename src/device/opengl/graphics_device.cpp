#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../i_graphics_device.h"
#include "../graphics_device_struct.h"
#include "platform/text_log.h"

#include "opengl/gl.h"
#include "opengl/glu.h"

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
    HGLRC hrc;
};

#include "graphics_device.h"

static VOID EnableOpenGL(HWND hWnd, HDC* hDC, HGLRC* hRC);
static VOID DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);

GraphicsDevice::GraphicsDevice()
{

}

GraphicsDevice::~GraphicsDevice()
{
    if(hdc)
        DisableOpenGL(hwnd, hdc, hrc);
}

void GraphicsDevice::drawPoint(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void GraphicsDevice::drawLine(int x1, int y1, int x2, int y2)
{
    glBegin(GL_LINES);
    glVertex2i(x1,y1);
    glVertex2i(x2,y2);
    glEnd();
}

void GraphicsDevice::setColor(float a, float r, float g, float b)
{
    glColor4f(r,g,b,a);
}

void GraphicsDevice::clearSufface()
{
    glClear(GL_COLOR_BUFFER_BIT);
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

void GraphicsDevice::initGraphics(GraphicsContext* context)
{
    hwnd = context->hwnd;
    EnableOpenGL(hwnd, &hdc, &hrc);
    glClearColor(0.0,0.0,0.0,0.0);
    glColor4f(1.0,1.0,1.0,1.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    RECT lpRect;
    GetClientRect(hwnd, &lpRect);  
    int hight = lpRect.bottom - lpRect.top;  
    int width = lpRect.right - lpRect.left;  

    gluOrtho2D(0.0,width,0.0,hight);
}

void GraphicsDevice::drawBegin()
{
   
}

void GraphicsDevice::drawEnd()
{
    glFlush();
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

//Enable OpenGL  
   
static VOID EnableOpenGL(HWND hWnd, HDC* hDC, HGLRC* hRC)
{  
    PIXELFORMATDESCRIPTOR pfd;  
    int iFormat;  
   
    // get the devicecontext (DC)  
    *hDC = GetDC( hWnd );  
   
    // set the pixelformat for the DC  
    ZeroMemory( &pfd, sizeof( pfd ) );  
    pfd.nSize        = sizeof(pfd);
    pfd.nVersion     = 1;
    pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
    pfd.cColorBits   = 32;
    iFormat = ChoosePixelFormat( *hDC, &pfd);  
    SetPixelFormat( *hDC, iFormat, &pfd );  
   
    // create andenable the render context (RC)  
    *hRC = wglCreateContext( *hDC );  
    wglMakeCurrent( *hDC, *hRC );  
}  

//Disable OpenGL  
   
static VOID DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
  wglMakeCurrent( NULL, NULL);  
  wglDeleteContext( hRC);  
  ReleaseDC( hWnd, hDC);  
}  
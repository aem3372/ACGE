#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../IGraphicsDevice.h"
#include "../GraphicsDeviceStruct.h"
#include "tools/TextLog.h"

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
// Pre-Builder define GLEW_STATIC
#define GLEW_STATIC 
#include <GL/glew.h>

class GraphicsDevice
: public IGraphicsDevice
{
public:
    GraphicsDevice();
    ~GraphicsDevice();

    virtual void initGraphics(GraphicsContext* context) override;
    virtual GraphicsDeviceInfo getDeviceInfo() override;
    virtual void drawBegin() override;
    virtual void drawEnd() override;
	virtual void draw(int x, int y) override;
	virtual void drawPoint(int x, int y) override;
    virtual void drawLine(int x1, int y1, int x2, int y2) override;
	virtual void drawImage(Image* img);
    virtual void setColor(float a, float r, float g, float b) override;
    virtual void clearSufface() override;
    virtual void destory() override;

private:
    HWND hwnd;
    HDC hdc;
    HGLRC hrc;
};

#include "GraphicsDevice.h"

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

void GraphicsDevice::draw(int x, int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
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

void GraphicsDevice::drawImage(Image* img)
{
	int width = img->getWidth();
    int height = img->getHeight();
    //int pitch = img->getPitch();

    unsigned char* bits = (unsigned char*)img->getData();
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            float r;;
            float g;
            float b;
            float a;
        }
    }
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

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEWn");
		return;
	}

}  

//Disable OpenGL  
   
static VOID DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
  wglMakeCurrent( NULL, NULL);  
  wglDeleteContext( hRC);  
  ReleaseDC( hWnd, hDC);  
}

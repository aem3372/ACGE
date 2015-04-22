#include <cstdio>
#include <cstdlib>
#include "windows.h"
#include "device/opengl/GraphicsDevice.h"
#include "tools/DynamicLinker.h"
// 全局变量:
HINSTANCE hInst;                        // 当前实例
HWND hWnd;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
ATOM                MyChildRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

void Init();
void Render();
void Cleanup();

#include "tools\PNGImage.h"

int main()
{
	HMODULE hModule = GetModuleHandle(NULL);
    hInst = (HINSTANCE)hModule;

    MyRegisterClass(hInst);

    // 执行应用程序初始化:
    if (!InitInstance (hInst, SW_SHOW))
    {
        return FALSE;
    }

    // 主消息循环:
    MSG msg;
    ZeroMemory( &msg, sizeof(msg) );
    
    while(msg.message != WM_QUIT)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);          
        }
        //没有消息时
        else
        {
            Render();
            Sleep(10);
        }
    }
    Cleanup();
    return (int) msg.wParam;

}

//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(NULL, IDI_WINLOGO);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = 0;
    wcex.lpszClassName  = TEXT("ACGE GDIPLUS TEST");
    wcex.hIconSm        = 0;

    return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hWnd = CreateWindow(
        TEXT("ACGE GDIPLUS TEST"), 
        TEXT("ACGE GDIPLUS TEST"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        0,
        CW_USEDEFAULT,
        0,
        NULL,
        NULL,
        hInstance,
        NULL
    );

   if (!hWnd)
   {
      return FALSE;
   }

   Init();

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;

    static float temp;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

IGraphicsDevice* gd;
GraphicsDeviceInfo info;

void Init()
{
	DynamicLinker* linker = DynamicLinker::getInstance();
	linker->loadLibrary("DeviceOpenGL", "device_opengl.dll");
	CreateInstanceFun fun = (CreateInstanceFun)linker->getProcAddress("DeviceOpenGL", "createInstance");

	gd = fun();

    if(gd)
    {
        GraphicsContext context;
        context.hwnd = hWnd;
        gd->initGraphics(&context);
        info = gd->getDeviceInfo();
        gd->setColor(1.0f, 1.0f, 0.0f, 0.0f);
    }
    else
    {
        printf("Get IGraphicsDevice Failed!\n");
    }

	Image* img = new PNGImage();
	img->loadWithFile("c:\\5.png");
	gd->drawImage(img);
}

void Render()
{
    static int x = 0, y = 400; 
    static int dx = 1;
    static int line_x = info.xres, line_y = 0;
    static int line_dy = 1;
    
    gd->drawBegin();
    gd->clearSufface();
    gd->drawPoint(x ,y);
    gd->drawLine(0,0,line_x,line_y);
    gd->drawEnd();

    if(x+dx >= info.xres || x+dx < 0)
    {
        dx = -dx;
    }
    if(line_y+line_dy >= info.yres || line_y+line_dy <0)
    {
        line_dy = -line_dy;
    }
    x += dx;
    line_y += line_dy;
}

void Cleanup()
{
    if(gd)
        gd->destory();
	DynamicLinker* linker = DynamicLinker::getInstance();
	linker->freeLibrary("DeviceOpenGL");
}

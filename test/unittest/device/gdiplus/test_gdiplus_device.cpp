#include <cstdio>
#include <cstdlib>
#include "windows.h"
#include "device/gdiplus/graphics_device.h"
#include "device/graphics_device_struct.h"
#include "device/i_graphics_device.h"
#include "device/i_graphics_drawpoint.h"
#include "device/i_graphics_argbcolor.h"
#include "device/i_graphics_clearsufface.h"

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
            Sleep(1000);
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
    int wmId, wmEvent;
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

IUnknow* pInstance;
IClearSufface* pClearSufface;
IDrawPoint* pDrawPoint;
GraphicsDeviceInfo info;
void Init()
{
    pInstance = createInstance(hWnd);
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

    if(pInstance->queryInterface("IGraphicsDevice", (void**)&pGraphicsDevice))
    {
        info = pGraphicsDevice->getDeviceInfo();
        pGraphicsDevice->release();
    }
    else
    {
        printf("queryInterface: IGraphicsDevice  failed!\n");
    }

    if(!pInstance->queryInterface("IClearSufface", (void**)&pClearSufface))
    {
        printf("queryInterface: IClearSufface  failed!\n");
    }
    if(!pInstance->queryInterface("IDrawPoint", (void**)&pDrawPoint))
    {
        printf("queryInterface: IDrawPoint  failed!\n");
    }
}

void Render()
{
    static int x = 0, y = 400; 
    static int dx = 1;
    pClearSufface->clearSufface();
    pDrawPoint->drawPoint(x ,y);
    if(x+dx >= info.xres || x+dx < 0)
    {
        dx = -dx;
    }

    x += dx;
}

void Cleanup()
{
    if(pDrawPoint)
        pDrawPoint->release();
    if(pInstance)
        pInstance->release();
}

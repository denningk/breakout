typedef int b32;

#define true 1
#define false 0

#define global_variable static
#define internal static

global_variable b32 running = true;

#include <windows.h>

typedef struct RenderBuffer
{
    int width, height;
    u32 *pixels;
    BITMAPINFO bitmap;
} RenderBuffer;

internal LRESULT 
CALLBACK WindowCallback(HWND window,UINT message,WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    
    switch (message)
    {
        case WM_CLOSE:
        case WM_DESTROY: {
            running = false;
        } break;
        
        default: {
            result = DefWindowProcA(window, message, wParam, lParam);
        }
    }
    return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    WNDCLASSA windowClass = {0};
    windowClass.style = CS_HREDRAW|CS_VREDRAW;
    windowClass.lpfnWndProc = WindowCallback;
    windowClass.lpszClassName = "GameWindowClass";
    
    RegisterClassA(&windowClass);
    
    HWND window =  CreateWindowExA(0, windowClass.lpszClassName,
                                   "Breakout",
                                   WS_VISIBLE|WS_OVERLAPPEDWINDOW,
                                   CW_USEDEFAULT, CW_USEDEFAULT,
                                   1280, 720, 0, 0, hInstance, 0);
    HDC hdc = GetDC(window);
    
    while (running)
    {
        // Input
        MSG message;
        while (PeekMessageA(&message, window, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        
        
        // Simulation
        int width, height;
        void *memory;
        BITMAPINFO bitmapInfo;
        StretchDIBits(hdc, 0, 0, width, height,
                      0, 0, width, height, memory,
                      &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
        // Render
    }
}

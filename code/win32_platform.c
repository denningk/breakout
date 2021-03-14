typedef int b32;

#define true 1
#define false 0

#define global_variable static
#define internal static

#include <windows.h>

global_variable b32 running = true;

LRESULT CALLBACK
WindowCallback(HWND window,UINT message,WPARAM wParam, LPARAM lParam)
{
    return DefWindowProcA(window, message, wParam, lParam);
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
    
    while (running)
    {
        // Input
        // Simulation
        // Render
    }
}

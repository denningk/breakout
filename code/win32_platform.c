#include "utils.c"
#include "math.c"

#include <windows.h>

typedef struct render_buffer
{
    // Platform non-specific
    int width, height;
    u32 *pixels;

    // Platform specific
    BITMAPINFO bitmapInfo;
} render_buffer;

global_variable render_buffer RENDER_BUFFER;

#include "software_renderer.c"

internal LRESULT
    CALLBACK
    WindowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    switch (message)
    {
    case WM_CLOSE:
    case WM_DESTROY:
    {
        running = false;
    }
    break;

    case WM_SIZE:
    {
        RECT rect;
        GetWindowRect(window, &rect);
        RENDER_BUFFER.width = rect.right - rect.left;
        RENDER_BUFFER.height = rect.bottom - rect.top;

        if (RENDER_BUFFER.pixels)
        {
            VirtualFree(RENDER_BUFFER.pixels, 0, MEM_RELEASE);
        }

        RENDER_BUFFER.pixels = VirtualAlloc(0, sizeof(u32) * RENDER_BUFFER.width * RENDER_BUFFER.height,
                                            MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        RENDER_BUFFER.bitmapInfo.bmiHeader.biSize = sizeof(RENDER_BUFFER.bitmapInfo.bmiHeader);
        RENDER_BUFFER.bitmapInfo.bmiHeader.biWidth = RENDER_BUFFER.width;
        RENDER_BUFFER.bitmapInfo.bmiHeader.biHeight = RENDER_BUFFER.height;
        RENDER_BUFFER.bitmapInfo.bmiHeader.biPlanes = 1;
        RENDER_BUFFER.bitmapInfo.bmiHeader.biBitCount = 32;
        RENDER_BUFFER.bitmapInfo.bmiHeader.biCompression = BI_RGB;
    }
    break;

    default:
    {
        result = DefWindowProcA(window, message, wParam, lParam);
    }
    }
    return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    WNDCLASSA windowClass = {0};
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowCallback;
    windowClass.lpszClassName = "GameWindowClass";

    RegisterClassA(&windowClass);

    HWND window = CreateWindowExA(0, windowClass.lpszClassName,
                                  "Breakout",
                                  WS_VISIBLE | WS_OVERLAPPEDWINDOW,
                                  CW_USEDEFAULT, CW_USEDEFAULT,
                                  1280, 720, 0, 0, hInstance, 0);
    HDC hdc = GetDC(window);

    while (running)
    {
        // Input
        MSG message;
        while (PeekMessageA(&message, window, 0, 0, PM_REMOVE))
        {
            switch (message.message)
            {
            case WM_SYSKEYDOWN:
            case WM_SYSKEYUP:
            case WM_KEYDOWN:
            case WM_KEYUP:
            {
            }
            break;

            default:
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
            }
        }

        // Simulation
        SimulateGame();

        ClearScreen(0x551100);

        DrawRectInPixels(20, 20, 50, 50, 0xffff00);

        // Render
        StretchDIBits(hdc, 0, 0, RENDER_BUFFER.width, RENDER_BUFFER.height,
                      0, 0, RENDER_BUFFER.width, RENDER_BUFFER.height, RENDER_BUFFER.pixels, &RENDER_BUFFER.bitmapInfo,
                      DIB_RGB_COLORS, SRCCOPY);
    }
}

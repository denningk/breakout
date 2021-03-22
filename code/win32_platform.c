#include "utils.c"
#include "math.c"

#include "platform_common.c"

#include <windows.h>

typedef struct RenderBuffer
{
    // Platform non-specific
    int width, height;
    u32 *pixels;

    // Platform specific
    BITMAPINFO bitmapInfo;
} RenderBuffer;

global_variable RenderBuffer RENDER_BUFFER;

#include "software_renderer.c"
#include "game.c"

internal LRESULT CALLBACK WindowCallback(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
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

    Input input = {0};

    while (running)
    {
        // Input
        for (int i = 0; i < BUTTON_COUNT; i++)
        {
            input.buttons[i].changed = false;
        }

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
                u32 vkCode = (u32)message.wParam;
                b32 wasDown = ((message.lParam & (1 << 30)) != 0);
                b32 isDown = ((message.lParam & (1 << 31)) == 0);

                if (vkCode == VK_LEFT)
                {
                    input.buttons[BUTTON_LEFT].changed = isDown != input.buttons[BUTTON_LEFT].isDown;
                    input.buttons[BUTTON_LEFT].isDown = isDown;
                }
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
        SimulateGame(&input);

        // Render
        StretchDIBits(hdc, 0, 0, RENDER_BUFFER.width, RENDER_BUFFER.height,
                      0, 0, RENDER_BUFFER.width, RENDER_BUFFER.height, RENDER_BUFFER.pixels, &RENDER_BUFFER.bitmapInfo,
                      DIB_RGB_COLORS, SRCCOPY);
    }
}

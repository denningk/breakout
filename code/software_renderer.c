internal void
ClearScreen(u32 color)
{
    u32 *pixel = RENDER_BUFFER.pixels;

    for (int y = 0; y < RENDER_BUFFER.height; y++)
    {
        for (int x = 0; x < RENDER_BUFFER.width; x++)
        {
            *pixel++ = color;
        }
    }
}

internal void
DrawRectInPixels(i32 x0, i32 y0, i32 x1, i32 y1, u32 color)
{
    x0 = Clamp(0, x0, RENDER_BUFFER.width);
    x1 = Clamp(0, x1, RENDER_BUFFER.width);
    y0 = Clamp(0, y0, RENDER_BUFFER.height);
    y1 = Clamp(0, y1, RENDER_BUFFER.height);

    for (int y = y0; y < y1; y++)
    {
        u32 *pixel = RENDER_BUFFER.pixels + x0 + RENDER_BUFFER.width * y;
        for (int x = x0; x < x1; x++)
        {
            *pixel++ = color;
        }
    }
}

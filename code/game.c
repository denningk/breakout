int p = 20;

internal void SimulateGame(Input *input)
{
    ClearScreen(0x551100);
    if (input->buttons[BUTTON_LEFT].isDown)
    {
        p += 20;
    }
    DrawRectInPixels(p, 20, p + 30, 50, 0xffff00);
}

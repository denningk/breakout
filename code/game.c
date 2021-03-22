internal void SimulateGame(Input *input)
{
    ClearScreen(0x551100);
    if (input->buttons[BUTTON_LEFT].isDown)
    {
        DrawRectInPixels(20, 20, 50, 50, 0xffff00);
    }
}

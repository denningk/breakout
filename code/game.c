int player_x = 30;
int player_y = 30;

internal void SimulateGame(Input *input)
{
    ClearScreen(0x551100);
    if (ButtonIsPressed(input, BUTTON_LEFT))
    {
        player_x -= 20;
    }
    if (ButtonIsPressed(input, BUTTON_RIGHT))
    {
        player_x += 20;
    }
    if (ButtonIsPressed(input, BUTTON_DOWN))
    {
        player_y -= 20;
    }
    if (ButtonIsPressed(input, BUTTON_UP))
    {
        player_y += 20;
    }
    DrawRectInPixels(player_x, player_y, player_x + 30, player_y + 30, 0xffff00);
}

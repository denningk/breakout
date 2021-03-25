typedef struct Button
{
    b32 isDown;
    b32 changed;
} Button;

typedef enum
{
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_UP,
    BUTTON_DOWN,

    BUTTON_COUNT
} ButtonType;

typedef struct Input
{
    int mouseX;
    int mouseY;

    Button buttons[BUTTON_COUNT];
} Input;

internal b32 ButtonIsPressed(Input *input, ButtonType button)
{
    return input->buttons[button].isDown && input->buttons[button].changed;
}

internal b32 ButtonIsReleased(Input *input, ButtonType button)
{
    return !input->buttons[button].isDown && input->buttons[button].changed;
}

internal b32 ButtonIsDown(Input *input, ButtonType button)
{
    return input->buttons[button].isDown;
}

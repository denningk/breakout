typedef struct Button
{
    b32 isDown;
    b32 changed;
} Button;

enum {
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_UP,
    BUTTON_DOWN,

    BUTTON_COUNT
};

typedef struct Input
{
    int mouseX;
    int mouseY;

    Button buttons[BUTTON_COUNT];
} Input;

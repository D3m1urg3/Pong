#ifndef __INPUT__
#define __INPUT__

enum Controls
{
    NONE,
    UP,
    DOWN,
    END
};

class Input
{
public:
    Input();
    ~Input();
    Controls get_keyboard_input();
};

#endif
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
    Controls check_for_input();
};

#endif
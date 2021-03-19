#include "globals.h"

int random_sign()
{
    bool is_even = (rand() % 2 == 0);
    if (is_even)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
#ifndef __COLLISION__
#define __COLLISION__

#include "SDL.h"
#include "globals.h"

class Box_collider
{
public:
    Box_collider(uint x, uint y, uint w, uint h);
    ~Box_collider();

    inline void set_position(uint x, uint y) { rect->x = x; rect->y = y; }
    inline SDL_Rect* get_rect() const { return rect; }
    bool is_colliding_with(Box_collider* other);
private:
    SDL_Rect* rect;
};

#endif

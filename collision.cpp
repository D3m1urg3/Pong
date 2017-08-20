#include "collision.h"

Box_collider::Box_collider(uint x, uint y, uint w, uint h)
{
    rect = new SDL_Rect();
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

Box_collider::~Box_collider()
{
    delete rect;
}

bool Box_collider::is_colliding_with(SDL_Rect* other)
{
    SDL_Rect intersection;
    return SDL_IntersectRect(rect, other, &intersection);
}
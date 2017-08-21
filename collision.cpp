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

bool Box_collider::is_colliding_with(Box_collider* other)
{
    if (other != nullptr)
    {
        SDL_Rect* other_rect = other->get_rect();
        if (other_rect != nullptr)
        {
            SDL_Rect* intersection = nullptr;
            return SDL_IntersectRect(rect, other_rect, intersection);
        }
    }
    return false;
}
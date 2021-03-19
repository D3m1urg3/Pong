#include "collision.h"

const Component_types Collider::ctype = COLLIDER;

// Box
Box_collider::Box_collider(uint x, uint y, uint w, uint h)
    :Collider(BOX)
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

bool Box_collider::is_colliding_with(Collider* other)
{
    if (other != nullptr)
    {
        if (other->get_type() == BOX)
        {
            Box_collider* other_box = static_cast<Box_collider*>(other);
            SDL_Rect* other_rect = other_box->get_rect();
            if (other_rect != nullptr)
            {
                SDL_Rect intersection;
                bool retval = SDL_IntersectRect(rect, other_rect, &intersection);
                return retval;
            }
        }
        else if (other->get_type() == EDGE)
        {
            Edge_collider* other_edge = static_cast<Edge_collider*>(other);
            return other_edge->is_colliding_with(this);
        }

    }
    return false;
}

// Edge
Edge_collider::Edge_collider(const Edge_position& position, uint scene_w, uint scene_h)
    :Collider(EDGE),
    position(position)
{
    switch (position)
    {
    case TOP:
        location = 0;
        break;
    case BOTTOM:
        location = scene_h;
        break;
    case LEFT:
        location = 0;
        break;
    case RIGHT:
        location = scene_w;
    }
}

bool Edge_collider::is_colliding_with(Collider* other)
{
    bool retval = false;
    if (other != nullptr)
    {
        if (other->get_type() == BOX)
        {
            Box_collider* other_box = static_cast<Box_collider*>(other);
            SDL_Rect* other_rect = other_box->get_rect();
            if (other_rect != nullptr)
            {
                switch (position)
                {
                case TOP:
                    retval = (other_rect->y < 0);
                    break;
                case BOTTOM:
                    retval = (other_rect->y > location);
                    break;
                case LEFT:
                    retval = (other_rect->x < 0);
                    break;
                case RIGHT:
                    retval = (other_rect->x > location);
                    break;
                }
            }
        }
    }
    return retval;
}

#include "physics.h"

Body::Body()
    :_x(0),
    _y(0),
    _vel_x(0),
    _vel_y(0)
{}

void Body::move(uint& x, uint& y)
{
    calculate_new_positions(x, y);
    _x = x;
    _y = y;
}
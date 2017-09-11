#include "physics.h"

Body::Body()
    :_x(0),
    _y(0),
    _vel_x(0),
    _vel_y(0)
{}

Body::Body(uint x, uint y, int v_x, int v_y) 
    :_x(x),
    _y(y),
    _vel_x(v_x),
    _vel_y(v_y)
{}

void Body::move(uint& x, uint& y)
{
    calculate_new_positions(x, y);
    _x = x;
    _y = y;
}
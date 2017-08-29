#ifndef __PHYSICS__
#define __PHYSICS__

#include "globals.h"

class Body
{
public:
    Body();
    ~Body() {};

    inline void set_position(uint x, uint y) { _x = x; _y = y; }
    inline void set_velocity(int v_x, int v_y) { _vel_x = v_x; _vel_y = v_y; }
    inline uint get_x() const { return _x; }
    inline uint get_y() const { return _y; }
    inline int get_velocity_x() const { return _vel_x; }
    inline int get_velocity_y() const { return _vel_y; }

    inline void calculate_new_positions(uint& x, uint& y) { x = _x + _vel_x; y = _y + _vel_y; }
    void move(uint& x, uint& y);
private:
    uint _x;
    uint _y;
    int _vel_x;
    int _vel_y;
};

#endif
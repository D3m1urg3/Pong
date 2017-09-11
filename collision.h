#ifndef __COLLISION__
#define __COLLISION__

#include "SDL.h"
#include "globals.h"

enum Collider_type
{
    BOX,
    EDGE
};

class Collider
{
public:
    Collider(Collider_type t) :type(t){};
    virtual ~Collider() {};
    
    Collider_type get_type() const { return type; }
    virtual bool is_colliding_with(Collider*) = 0;
    virtual void set_position(uint x, uint y) = 0;
protected:
    Collider_type type;
};

class Box_collider : public Collider
{
public:
    Box_collider(uint x, uint y, uint w, uint h);
    ~Box_collider();

    void set_position(uint x, uint y) { rect->x = x; rect->y = y; }
    inline SDL_Rect* get_rect() const { return rect; }
    bool is_colliding_with(Collider* other);
private:
    SDL_Rect* rect;
};

enum Edge_position
{
    TOP,
    BOTTOM,
    LEFT,
    RIGHT
};

class Edge_collider : public Collider
{
public:
    Edge_collider(const Edge_position& position, uint scene_w, uint scene_h);
    ~Edge_collider() {};

    void set_position(uint x, uint y) {}
    bool is_colliding_with(Collider* other);
private:
    Edge_position position;
    uint location;
};
#endif

#ifndef __ENTITIES__
#define __ENTITIES__

#include "graphics.h"

class Entity 
{
public:
    Entity(uint x_, uint  y_);
    virtual ~Entity();
    void extract_sprite(Texture* spritesheet, uint s_x, uint s_y, uint s_w, uint s_h);
    void draw(Renderer* render, uint x, uint y);
protected:
    double x;
    double y;
    Sprite* sprite;
};

class Ball : public Entity
{
public:
    Ball(uint x_, uint  y_);
    ~Ball();
};

class Paddle : public Entity
{
public:
    Paddle(uint x_, uint  y_);
    ~Paddle();
};

class Number : public Entity
{
public:
    Number(uint x_, uint  y_);
    ~Number();
private:
    Sprite* sprite;
};
#endif

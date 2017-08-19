#ifndef __ENTITIES__
#define __ENTITIES__

#include "graphics.h"

class Entity 
{
public:
    Entity(int x_, int  y_, int  w_, int  h_):x(x_), y(y_), w(w_), h(h_){}
    virtual ~Entity() {}
protected:
    double x;
    double y;
    double w;
    double h;
};

class Ball : public Entity
{
public:
    Ball(Texture* spritesheet, int x_, int  y_, int  w_, int  h_);
    ~Ball();
    void draw(Renderer* render);
private:
    static const int sprt_x;
    static const int sprt_y;
    static const int sprt_w;
    static const int sprt_h;
    Sprite* sprite;
};

#endif

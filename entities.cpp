#include "entities.h"

const int Ball::sprt_x = 73;    //pixels
const int Ball::sprt_y = 104;   //pixels
const int Ball::sprt_w = 4;     //pixels
const int Ball::sprt_h = 4;     //pixels

Ball::Ball(Texture* spritesheet, uint x_, uint  y_, uint  w_, uint  h_)
    :Entity(x_, y_, w_, h_)
{
    sprite = new Sprite(spritesheet, sprt_x, sprt_y, sprt_w, sprt_h);
}

Ball::~Ball()
{
    delete sprite;
}

void Ball::draw(Renderer* render, uint x, uint y)
{
    if (sprite != nullptr)
    {
        sprite->set_dst_rect(x, y, sprt_w, sprt_h);
        sprite->draw(render);
    }
}
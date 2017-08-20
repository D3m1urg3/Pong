#include "entities.h"

// Entity
Entity::Entity(uint x_, uint  y_)
    :x(x_),
    y(y_),
    sprite(nullptr)
{}

Entity::~Entity()
{
    delete sprite;
}

void Entity::extract_sprite(Texture* spritesheet, uint s_x, uint s_y, uint s_w, uint s_h)
{
    if (sprite == nullptr)
    {
        sprite = new Sprite(spritesheet, s_x, s_y, s_w, s_h);
    }
}

void Entity::draw(Renderer* render, uint x, uint y)
{
    if (sprite != nullptr)
    {
        sprite->set_dst_rect(x, y, sprite->get_sprite_width(), sprite->get_sprite_height());
        sprite->draw(render);
    }
}

// Ball
/*
const int Ball::sprt_x = 73;    //pixels
const int Ball::sprt_y = 104;   //pixels
const int Ball::sprt_w = 4;     //pixels
const int Ball::sprt_h = 4;     //pixels
*/

Ball::Ball(uint x_, uint  y_)
    :Entity(x_, y_)
{
}

Ball::~Ball()
{
}


// Paddle
/*
const int Paddle::sprt_x = 29;    //pixels
const int Paddle::sprt_y = 94;    //pixels
const int Paddle::sprt_w = 4;     //pixels
const int Paddle::sprt_h = 14;    //pixels
*/

Paddle::Paddle(uint x_, uint  y_)
    :Entity(x_, y_)
{
}

Paddle::~Paddle()
{
}

// Number
Number::Number(uint x_, uint  y_)
    :Entity(x_, y_)
{
}

Number::~Number()
{
}

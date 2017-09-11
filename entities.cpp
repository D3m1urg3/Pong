#include "entities.h"

// Entity
Entity::Entity(uint x, uint  y)
    :_x(x),
    _y(y),
    _x_min(-1),
    _x_max(-1),
    _y_min(-1),
    _y_max(-1),
    sprite(nullptr),
    collider(nullptr),
    body(nullptr),
    mind(nullptr)
{}

Entity::~Entity()
{
    delete sprite;
    delete collider;
    delete body;
    delete mind;
}

bool Entity::attach(AI* brain)
{
    if (brain != nullptr)
    {
        delete mind;
        mind = brain;
        return true;
    }
    return false;
}

bool Entity::attach(Body* bdy)
{
    if (bdy != nullptr)
    {
        delete body;
        body = bdy;
        return true;
    }
    return false;
}

void Entity::set_position(uint x, uint y)
{
    _x = x; 
    _y = y;
    if (collider != nullptr)
    {
        collider->set_position(x, y);
    }
    if (body != nullptr)
    {
        body->set_position(x, y);
    }
}

void Entity::set_max_positions(int x_min, int x_max, int y_min, int y_max) 
{ 
    _x_min = x_min; 
    _x_max = x_max; 
    _y_min = y_min; 
    _y_max = y_max; 
}

void Entity::extract_sprite(Texture* spritesheet, uint s_x, uint s_y, uint s_w, uint s_h)
{
    if (sprite == nullptr)
    {
        sprite = new Sprite(spritesheet, s_x, s_y, s_w, s_h);
    }
}

void Entity::attach_box_collider(uint x, uint y, uint w, uint h)
{
    delete collider;
    collider = nullptr;
    collider = new Box_collider(x, y, w, h);
}

void Entity::attach_edge_collider(const Edge_position& pos, uint scene_w, uint scene_h)
{
    delete collider;
    collider = nullptr;
    collider = new Edge_collider(pos, scene_w, scene_h);
}

void Entity::draw(Renderer* render, uint x, uint y)
{
    if (sprite != nullptr)
    {
        sprite->set_dst_rect(x, y, sprite->get_sprite_width(), sprite->get_sprite_height());
        sprite->draw(render);
    }
}

void Entity::draw(Renderer* render)
{
    if (sprite != nullptr)
    {
        sprite->set_dst_rect(_x, _y, sprite->get_sprite_width(), sprite->get_sprite_height());
        sprite->draw(render);
    }
}

bool Entity::is_valid_position(uint x, uint y)
{
    bool valid_x = true;
    if (_x_min >= 0 && _x_max >= 0)
    {
        valid_x = (_x_min <= x) && (x <= _x_max);
    }
    bool valid_y = true;
    if (_y_min >= 0 && _y_max >= 0)
    {
        valid_y = (_y_min <= y) && (y <= _y_max);
    }

    return (valid_x && valid_y);
}

void Entity::move()
{
    if (body != nullptr)
    {
        uint x_new = _x;
        uint y_new = _y;
        body->calculate_new_positions(x_new, y_new);
        if(is_valid_position(x_new, y_new))
        {
            body->move(_x,_y);
            if (collider != nullptr)
            {
                collider->set_position(_x, _y);
            }
        }
    }
}

// Scoreboard
Scoreboard::Scoreboard(Texture* spritesheet, uint x, uint y)
    :score(0)
{
    SDL_Rect numbers_specs[10] =
    {   // {x,y,w,h}
        {4, 3, 16, 32},   //0
        {23, 3, 4, 32},   //1
        {30, 3, 16, 32},  //2
        {49, 3, 16, 32},  //3
        {68, 3, 16, 32},  //4
        {87, 3, 16, 32},  //5
        {106, 3, 16, 32}, //6
        {125, 3, 16, 32}, //7
        {144, 3, 16, 32}, //8
        {163, 3, 16, 32}, //9
    };

    for (int i = 0; i < 10; ++i)
    {
        numbers[i] = new Entity(x, y);
        numbers[i]->extract_sprite(spritesheet, numbers_specs[i].x, numbers_specs[i].y, numbers_specs[i].w, numbers_specs[i].h);
    }
}

Scoreboard::~Scoreboard()
{
    for (int i = 0; i < 10; ++i)
    {
        delete numbers[i];
    }
}

void Scoreboard::draw(Renderer* render)
{
    if (score < 10)
    {
        numbers[score]->draw(render);
    }
}

// AI
AI::AI(Body* body, Entity* ball)
    :mybody(body),
    ball(ball)
{}

void AI::act()
{
    bool do_something = (rand() % 100 <= 20);
    int ball_position_error = rand() % 4 - 2;
    if (do_something && ball != nullptr && mybody != nullptr)
    {
        int ball_y = ball->get_y() + ball_position_error;
        if (ball_y < mybody->get_y())
        {
            mybody->set_velocity(0, -4);
        }
        else if (ball_y > mybody->get_y())
        {
            mybody->set_velocity(0, 4);
        }
        else
        {
            mybody->set_velocity(0, 0);
        }
    }
}
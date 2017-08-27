#include "entities.h"

// Entity
Entity::Entity(uint x, uint  y)
    :_x(x),
    _y(y),
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

void Entity::attach_body(uint x, uint y, uint w, uint h)
{
    delete body;
    body = nullptr;
    body = new Body();
    body->set_position(x + w / 2, y + h / 2); // Center of gravity of entity
}
void Entity::attach_mind(Entity* ball)
{
    delete mind;
    mind = nullptr;
    if (ball != nullptr && body != nullptr)
    {
        mind = new AI(body, ball);
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

void Entity::draw(Renderer* render)
{
    if (sprite != nullptr)
    {
        sprite->set_dst_rect(_x, _y, sprite->get_sprite_width(), sprite->get_sprite_height());
        sprite->draw(render);
    }
}

void Entity::move()
{
    if (body != nullptr)
    {
        body->move(_x, _y);
        if (collider != nullptr)
        {
            collider->set_position(_x, _y);
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
    if (do_something && ball != nullptr && mybody != nullptr)
    {
        uint ball_y = ball->get_y();
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
#include "entities.h"

// Entity
Entity::Entity(uint x, uint  y)
    :_x(x),
    _y(y),
    sprite(nullptr),
    collider(nullptr),
    body(nullptr)
{}

Entity::~Entity()
{
    delete sprite;
    delete collider;
    delete body;
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

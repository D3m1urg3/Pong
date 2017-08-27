#ifndef __ENTITIES__
#define __ENTITIES__

#include "graphics.h"
#include "physics.h"
#include "collision.h"
#include <vector>

class Entity 
{
public:
    Entity(uint x, uint  y);
    virtual ~Entity();

    Sprite* sprite;
    Collider* collider;
    Body* body;

    void extract_sprite(Texture* spritesheet, uint s_x, uint s_y, uint s_w, uint s_h);
    virtual void set_position(uint x, uint y);
    // Collisions
    virtual void attach_box_collider(uint x, uint y, uint w, uint h);
    virtual void attach_edge_collider(const Edge_position& pos, uint scene_w, uint scene_h);
    // Physics
    virtual void attach_body(uint x, uint y, uint w, uint h);
    virtual void move();
    // Render
    void draw(Renderer* render);
    void draw(Renderer* render, uint x, uint y);
protected:
    uint _x;
    uint _y;
};

class Scoreboard
{
public:
    Scoreboard(Texture* spritesheet, uint x, uint y);
    ~Scoreboard();
    
    inline void raise() { ++score; }
    void draw(Renderer* render);
private:
    uint score;
    Entity* numbers[10];
};
#endif

#ifndef __ENTITIES__
#define __ENTITIES__

#include "graphics.h"
#include "physics.h"
#include "collision.h"
#include <vector>

class AI;

class Entity 
{
public:
    Entity(uint x, uint  y);
    virtual ~Entity();

    Sprite* sprite;
    Collider* collider;
    Body* body;
    AI* mind;

    void set_position(uint x, uint y);
    void set_max_positions(int x_min, int x_max, int y_min, int y_max);
    inline uint get_x() const { return _x; }
    inline uint get_y() const { return _y; }

    // Collisions
    void attach_box_collider(uint x, uint y, uint w, uint h);
    virtual void attach_edge_collider(const Edge_position& pos, uint scene_w, uint scene_h);

    // Physics
    void attach_body(uint x, uint y, uint w, uint h);
    void move();

    // AI
    bool attach(AI* brain);

    // Sprites and render
    void extract_sprite(Texture* spritesheet, uint s_x, uint s_y, uint s_w, uint s_h);
    void draw(Renderer* render);
    void draw(Renderer* render, uint x, uint y);

protected:
    uint _x;
    uint _y;
    int _x_min;
    int _x_max;
    int _y_min;
    int _y_max;

    bool is_valid_position(uint x, uint y);
};

class Scoreboard
{
public:
    Scoreboard(Texture* spritesheet, uint x, uint y);
    ~Scoreboard();
    
    inline uint get_score() { return score; }
    inline void raise() { ++score; }
    void draw(Renderer* render);
private:
    uint score;
    Entity* numbers[10];
};

class AI
{
public:
    AI(Body* body, Entity* ball);
    ~AI() {}

    void act();
private:
    Body* mybody;
    const Entity* ball;
};
#endif

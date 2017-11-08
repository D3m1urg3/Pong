#ifndef __ENTITIES__
#define __ENTITIES__

#include "graphics.h"
#include "sound.h"
#include "physics.h"
#include "collision.h"
#include "input.h"
#include <vector>
#include <algorithm>

class AI;

class Entity 
{
public:
    Entity(uint x, uint  y);
    Entity(uint x, uint  y, std::string tag);
    virtual ~Entity();

    Sprite* sprite;
    Collider* collider;
    Body* body;
    AI* mind;

    bool attach(Sprite* sprt);
    bool attach(Collider* col);
    bool attach(Body* bdy);
    bool attach(AI* brain);

    void                 set_position(uint x, uint y);
    void                 set_max_positions(int x_min, int x_max, int y_min, int y_max);
    inline uint          get_x() const { return _x; }
    inline uint          get_y() const { return _y; }
    std::vector<Entity*> get_entity_list() const { return entities; }
    const std::string    id() const { return tag; }

    Entity* search_for_entity(std::string identifier);
    void    move();
    void    draw(Renderer* render);
    void    draw(Renderer* render, uint x, uint y);

    virtual void update(){}

protected:
    static std::vector<Entity*> entities;
    const std::string tag;

    uint _x;
    uint _y;
    int _x_min;
    int _x_max;
    int _y_min;
    int _y_max;

    bool is_valid_position(uint x, uint y);
};

class Player : public Entity
{
public:
    Player(Texture* spritesheet, Controls* ctrl, uint x, uint y, uint v_x, uint v_y);
    ~Player();

    void update();
private:
    Controls* control;
    const uint paddle_vel_x;
    const uint paddle_vel_y;
};

class Opponent : public Entity
{
public:
    Opponent(Texture* spritesheet, uint x, uint y, uint v_x, uint v_y);
    ~Opponent();

    void update();
private:
    const uint paddle_vel_x;
    const uint paddle_vel_y;
};

class Ball : public Entity
{
public:
    Ball(Texture* spritesheet, uint x, uint y, uint v_x, uint v_y, Sound* paddle, Sound* edge, Sound* score);
    ~Ball();

    void update();
private:
    const uint ball_init_pos_x;
    const uint ball_init_pos_y;
    const uint ball_init_vel_x;
    const uint ball_init_vel_y;
    Sound* paddle_beep;
    Sound* edge_beep;
    Sound* score_beep;
};

class Border : public Entity
{
public:
    Border(Edge_position pos, uint screen_w, uint screen_h, std::string id);
    ~Border();

    inline Edge_position position() const { return _position; }
private:
    Edge_position _position;
};

class Scoreboard : public Entity
{
public:
    Scoreboard(Texture* spritesheet, uint x, uint y, std::string board_id);
    ~Scoreboard();
    
    inline uint get_score() { return score; }
    inline void raise() { ++score; }
    void draw(Renderer* render);
private:
    uint score;
    Sprite* numbers[10];
};

class AI
{
public:
    AI(Body* body, Entity* ball);
    ~AI() {}

    Component_types component_type() const { return ctype; }
    void act();
private:
    static const Component_types ctype;
    Body* mybody;
    const Entity* ball;
};
#endif

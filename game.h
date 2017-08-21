#ifndef __GAME__
#define __GAME__

#include "graphics.h"
#include "input.h"
#include "entities.h"
#include "globals.h"

#define SCREEN_WIDTH 192 // pixels
#define SCREEN_HEIGHT 242 // pixels

const uint ball_sprite_x = 73;      //pixels
const uint ball_sprite_y = 104;     //pixels
const uint ball_sprite_w = 4;       //pixels
const uint ball_sprite_h = 4;       //pixels
const uint paddle_sprite_x = 29;    //pixels
const uint paddle_sprite_y = 94;    //pixels
const uint paddle_sprite_w = 4;     //pixels
const uint paddle_sprite_h = 14;    //pixels
const int paddle_velocity_x = 0;   //pixels/update
const int paddle_velocity_y = 4;   //pixels/update
const uint player_init_x = 4;
const uint player_init_y = (SCREEN_HEIGHT-paddle_sprite_h)/2;

const char spritesheet_fullfilename[] = "Resources/sprites.bmp";

enum Game_state
{
    INITIALIZING,
    READY_TO_RUN,
    RUNNING,
    FINISHED
};

class Game
{
public:
    Game();
    ~Game();

    bool init_ok();
    void update();
    inline void draw_ball() { ball->draw(render, 20, 20); }
    inline Game_state get_state() const { return state; }
private:
    Game_state state;
    Renderer* render;
    Input* input;
    Texture* spritesheet;
    Sprite* background;
    Sprite* middle_line;
    Ball* ball;
    Paddle* player;
    Paddle* opponent;

    void update_entities();
    void draw();

    void draw_background();
};

#endif 
#ifndef __GAME__
#define __GAME__

#include "graphics.h"
#include "input.h"
#include "entities.h"

#define SCREEN_WIDTH 192 // pixels
#define SCREEN_HEIGHT 242 // pixels

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

    void draw_background();
};

#endif 
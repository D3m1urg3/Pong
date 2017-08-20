#ifndef __GAME__
#define __GAME__

#include "graphics.h"
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
    void draw_background();
    inline void draw_ball() { ball->draw(render, 20, 20); }
    inline Game_state get_state() const { return state; }
private:
    Game_state state;
    Renderer* render;
    Texture* spritesheet;
    Sprite* background;
    Sprite* middle_line;
    Ball* ball;
};

#endif 
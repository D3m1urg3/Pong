#ifndef __GAME__
#define __GAME__

#include "graphics.h"
#include "entities.h"

#define SCREEN_WIDTH 192 // pixels
#define SCREEN_HEIGHT 242 // pixels

const char spritesheet_fullfilename[] = "Resources/sprites.bmp";

class Game
{
public:
    Game();
    ~Game();
    inline void draw_background() { background->draw(render); }
    inline void draw_ball() { ball->draw(render, 20, 20); }
private:
    Renderer* render;
    Texture* spritesheet;
    Sprite* background;
    Ball* ball;
};

#endif 
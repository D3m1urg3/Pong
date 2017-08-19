#ifndef __GAME__
#define __GAME__

#include "graphics.h"
#include "entities.h"

#define SCREEN_WIDTH 192 // pixels
#define SCREEN_HEIGHT 242 // pixels

const char spritesheet_fullfilename[] = "Resources/sprites.png";

class Game
{
public:
    Game();
    ~Game();
private:
    Renderer* render;
    Texture* spritesheet;
    Ball* ball;
};

#endif 
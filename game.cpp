#include "game.h"

Game::Game()
{
    render = new Renderer("Pong", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    spritesheet = new Texture(spritesheet_fullfilename);
    ball = new Ball(spritesheet, 50, 50, 0, 0);
}

Game::~Game()
{
    delete render;
    delete spritesheet;
    delete ball;
}
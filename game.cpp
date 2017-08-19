#include "game.h"

Game::Game()
{
    render = new Renderer("Pong", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    spritesheet = new Texture(spritesheet_fullfilename);
    background = new Sprite(spritesheet, 0, 150, 20, 20);
    background->set_dst_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    ball = new Ball(spritesheet, 50, 50, 0, 0);
}

Game::~Game()
{
    delete render;
    delete spritesheet;
    delete background;
    delete ball;
}
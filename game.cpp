#include "game.h"

Game::Game()
{
    state = INITIALIZING;
    render = new Renderer("Pong", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    spritesheet = new Texture(spritesheet_fullfilename);
    // Backgound Sprites
    background = new Sprite(spritesheet, 0, 150, 20, 20);
    background->set_dst_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    middle_line = new Sprite(spritesheet, 186, 0, 1, SCREEN_HEIGHT);
    middle_line->set_dst_rect(96, 0, 1, SCREEN_HEIGHT);
}

Game::~Game()
{
    delete render;
    delete spritesheet;
    delete background;
    delete middle_line;
    delete ball;
}

void Game::update()
{

}

void Game::draw_background()
{
    background->draw(render);
    middle_line->draw(render);
}
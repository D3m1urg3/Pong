#include "game.h"

Game::Game()
{
    state = INITIALIZING;
    render = new Renderer("Pong", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    spritesheet = new Texture(spritesheet_fullfilename);
    // Input
    input = new Input();
    // Backgound Sprites
    background = new Sprite(spritesheet, 0, 150, 20, 20);
    background->set_dst_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    middle_line = new Sprite(spritesheet, 186, 0, 1, SCREEN_HEIGHT);
    middle_line->set_dst_rect(96, 0, 1, SCREEN_HEIGHT);
    // Ball
    ball = new Ball(50, 50);
    ball->extract_sprite(spritesheet, ball_sprite_x, ball_sprite_y, ball_sprite_w, ball_sprite_h);
    ball->attach_body(50, 50, ball_sprite_w, ball_sprite_h);
    ball->attach_collider(50, 50, ball_sprite_w, ball_sprite_h);
    // Player
    player = new Paddle(player_init_x, player_init_y);
    player->extract_sprite(spritesheet, paddle_sprite_x, paddle_sprite_y, paddle_sprite_w, paddle_sprite_h);
    player->attach_body(player_init_x, player_init_y, paddle_sprite_w, paddle_sprite_h);
    player->attach_collider(player_init_x, player_init_y, paddle_sprite_w, paddle_sprite_h);

    state = READY_TO_RUN;
}

Game::~Game()
{
    delete render;
    delete input;
    delete spritesheet;
    delete background;
    delete middle_line;
    delete ball;
    delete player;
    delete opponent;
}

bool Game::init_ok()
{
    bool ready_to_run = (state == READY_TO_RUN);
    bool render_ok = (render != nullptr);
    bool spritesheet_ok = (spritesheet != nullptr);
    bool background_ok = (background != nullptr) && (middle_line != nullptr);
    bool input_ok = (input != nullptr);
    bool entities_ok = true;
    Entity* entities[] = { player, ball };
    for (int i = 0; i < 2; ++i)
    {
        if (entities[i] == nullptr)
        {
            entities_ok = false;
            break;
        }
    }
    return ready_to_run && render_ok && spritesheet_ok && background_ok && input_ok && entities_ok;
}

void Game::update()
{
    state = RUNNING;
    update_entities();
    draw();
}

void Game::draw_background()
{
    background->draw(render);
    middle_line->draw(render);
}

void Game::update_entities()
{
    // update player
    if (input != nullptr)
    {
        Controls controls = input->check_for_input();
        switch (controls)
        {
        case END:
            state = FINISHED;
            break;
        case NONE:
            player->body->set_velocity(0, 0);
            break;
        case UP:
            player->body->set_velocity(paddle_velocity_x, -1*paddle_velocity_y);
            break;
        case DOWN:
            player->body->set_velocity(paddle_velocity_x, paddle_velocity_y);
            break;
        }
    }
    player->move();

    // update opponent
    // ... AI

    // update ball
    int ball_vel_x = ball->body->get_velocity_x();
    int ball_vel_y = ball->body->get_velocity_y();
    //if (ball->collider->is_colliding_with(player->collider) || ball->collider->is_colliding_with(opponent->collider) )
    if (ball->collider->is_colliding_with(player->collider))
    {
        ball->body->set_velocity(-1 * ball_vel_x, ball_vel_y);
    }
    ball->move();
}

void Game::draw()
{
    render->clear_screen();
    background->draw(render);
    middle_line->draw(render);
    player->draw(render);
    ball->draw(render);
}
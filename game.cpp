#include "game.h"

Game::Game()
{
    state = INITIALIZING;
    // Graphics
    render = new Renderer("Pong", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT);
    spritesheet = new Texture(spritesheet_fullfilename);
    // Input
    input = new Input();
    // Sounds
    init_sound();
    paddle_beep = new Sound(paddle_sound_fullfilename);
    edge_beep = new Sound(edge_sound_fullfilename);
    point_beep = new Sound(point_sound_fullfilename);
    // Backgound Sprites
    background = new Sprite(spritesheet, 0, 150, 20, 20);
    background->set_dst_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    middle_line = new Sprite(spritesheet, 186, 0, 1, SCREEN_HEIGHT);
    middle_line->set_dst_rect(96, 0, 1, SCREEN_HEIGHT);
    // Ball
    ball = new Entity(ball_init_x, ball_init_y);
    ball->attach(new Sprite(spritesheet, ball_sprite_x, ball_sprite_y, ball_sprite_w, ball_sprite_h));
    ball->attach(new Body( ball_init_x +  ball_sprite_w/2, ball_init_y +  ball_sprite_w/2, 0, 0 )); // Center of the entity
    ball->attach_box_collider(ball_init_x, ball_init_y, ball_sprite_w, ball_sprite_h);
    ball->body->set_velocity(ball_init_vel_x, ball_init_vel_y);
    // Player
    player = new Entity(player_init_x, player_init_y);
    player->set_max_positions(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    player->attach(new Sprite(spritesheet, paddle_sprite_x, paddle_sprite_y, paddle_sprite_w, paddle_sprite_h));
    player->attach(new Body( player_init_x +  paddle_sprite_w/2, player_init_y +  paddle_sprite_w/2, 0, 0 )); // Center of the entity
    player->attach_box_collider(player_init_x, player_init_y, paddle_sprite_w, paddle_sprite_h);
    player_scoreboard = new Scoreboard(spritesheet, 10, 10);
    // Opponent
    opponent = new Entity(opponent_init_x, opponent_init_y);
    opponent->set_max_positions(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
    opponent->attach(new Sprite(spritesheet, paddle_sprite_x, paddle_sprite_y, paddle_sprite_w, paddle_sprite_h));
    opponent->attach(new Body( opponent_init_x +  paddle_sprite_w/2, opponent_init_y +  paddle_sprite_w/2, 0, 0 )); // Center of the entity
    opponent->attach_box_collider(opponent_init_x, opponent_init_y, paddle_sprite_w, paddle_sprite_h);
    opponent->attach(new AI(opponent->body, ball));
    opponent_scoreboard = new Scoreboard(spritesheet, SCREEN_WIDTH - 26, 10); // 26 = 10 (margin) + 16 (tipical number size) 
    // Edges
    edge_top = new Entity(0, 0);
    edge_top->attach_edge_collider(TOP, SCREEN_WIDTH, SCREEN_HEIGHT);
    edge_bottom = new Entity(0, SCREEN_HEIGHT);
    edge_bottom->attach_edge_collider(BOTTOM, SCREEN_WIDTH, SCREEN_HEIGHT);
    edge_left = new Entity(0, 0);
    edge_left->attach_edge_collider(LEFT, SCREEN_WIDTH, SCREEN_HEIGHT);
    edge_right = new Entity(SCREEN_WIDTH, 0);
    edge_right->attach_edge_collider(RIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);

    state = READY_TO_RUN;
}

Game::~Game()
{
    delete render;
    delete input;
    delete paddle_beep;
    delete edge_beep;
    delete point_beep;
    delete spritesheet;
    delete background;
    delete middle_line;
    delete ball;
    delete player;
    delete opponent;
    delete player_scoreboard;
    delete opponent_scoreboard;
}

bool Game::init_ok()
{
    bool ready_to_run = (state == READY_TO_RUN);
    bool render_ok = (render != nullptr);
    bool spritesheet_ok = (spritesheet != nullptr);
    bool background_ok = (background != nullptr) && (middle_line != nullptr);
    bool input_ok = (input != nullptr);
    bool entities_ok = true;
    Entity* entities[] = { player, ball, opponent };
    for (int i = 0; i < 3; ++i)
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
    opponent->mind->act();
    opponent->move();

    // update ball
    ball->move();
    int ball_vel_x = ball->body->get_velocity_x();
    int ball_vel_y = ball->body->get_velocity_y();
    if (ball->collider->is_colliding_with(player->collider) || ball->collider->is_colliding_with(opponent->collider) )
    {
        paddle_beep->play();
        ball->body->set_velocity(-1 * ball_vel_x, ball_vel_y);
    }
    else if (ball->collider->is_colliding_with(edge_top->collider) || ball->collider->is_colliding_with(edge_bottom->collider))
    {
        edge_beep->play();
        ball->body->set_velocity(ball_vel_x, -1 * ball_vel_y);
    }
    else if (ball->collider->is_colliding_with(edge_left->collider))
    {
        point_beep->play();
        opponent_scoreboard->raise();
        ball->set_position(ball_init_x, ball_init_y);
    }
    else if (ball->collider->is_colliding_with(edge_right->collider))
    {
        point_beep->play();
        player_scoreboard->raise();
        ball->set_position(ball_init_x, ball_init_y);
        ball->body->set_velocity( random_sign() * ball_init_vel_x, random_sign() * ball_init_vel_y );
    }

    // Check win conditions
    if (player_scoreboard->get_score() == 9 || opponent_scoreboard->get_score() == 9)
    {
        state = FINISHED;
    }
}

void Game::draw()
{
    render->clear_screen();
    background->draw(render);
    middle_line->draw(render);
    player->draw(render);
    player_scoreboard->draw(render);
    opponent->draw(render);
    opponent_scoreboard->draw(render);
    ball->draw(render);
}
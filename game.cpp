#include "game.h"

Game::Game()
{
    state = INITIALIZING;

    // Graphics
    render      = new Renderer("Pong", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT);
    spritesheet = new Texture(spritesheet_fullfilename);

    // Input
    input   = new Input();
    control = NONE;

    // Sounds
    init_sound();
    paddle_beep = new Sound(paddle_sound_fullfilename);
    edge_beep   = new Sound(edge_sound_fullfilename);
    point_beep  = new Sound(point_sound_fullfilename);

    // Backgound Sprites
    background  = new Sprite(spritesheet, 0, 150, 20, 20);
    background->set_dst_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    middle_line = new Sprite(spritesheet, 186, 0, 1, SCREEN_HEIGHT);
    middle_line->set_dst_rect(96, 0, 1, SCREEN_HEIGHT);

    // Entities
    ball                = new Ball(spritesheet, ball_init_x, ball_init_y, ball_init_vel_x, ball_init_vel_y, paddle_beep, edge_beep, point_beep);
    player              = new Player(spritesheet, &control, player_init_x, player_init_y, paddle_velocity_x, paddle_velocity_y);
    opponent            = new Opponent(spritesheet, opponent_init_x, opponent_init_y, paddle_velocity_x, paddle_velocity_y);
    player_scoreboard   = new Scoreboard(spritesheet, 10, 10, "player_scoreboard");
    opponent_scoreboard = new Scoreboard(spritesheet, SCREEN_WIDTH - 26, 10, "opponent_scoreboard"); // 26 = 10 (margin) + 16 (tipical number size) 

    // Edges
    edge_top    = new Border(TOP, SCREEN_WIDTH, SCREEN_HEIGHT, "top_border");
    edge_bottom = new Border(BOTTOM, SCREEN_WIDTH, SCREEN_HEIGHT, "bottom_border");
    edge_left   = new Border(LEFT, SCREEN_WIDTH, SCREEN_HEIGHT, "left_border");
    edge_right  = new Border(RIGHT, SCREEN_WIDTH, SCREEN_HEIGHT, "right_border");

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

    Entity* entities[9] = { player, ball, opponent, edge_top, edge_bottom, edge_left, edge_right, player_scoreboard, opponent_scoreboard };
    for (int i = 0; i < 9; ++i)
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

void Game::update_entities()
{
    // Check for quit
    if (control == END)
    {
        state = FINISHED;
    }

    // Input 
    if (input != nullptr)
    {
        control = input->check_for_input();
    }

    // Update player
    player->update();

    // update opponent
    opponent->update();

    // update ball
    ball->update();

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
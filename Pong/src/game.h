#ifndef __GAME__
#define __GAME__

#include "graphics.h"
#include "sound.h"
#include "input.h"
#include "entities.h"
#include "globals.h"

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

    bool init_ok();
    void update();
    inline Game_state get_state() const { return state; }
private:
    Game_state state;
    Controls  control;
    Renderer* render;
    Input* input;
    Texture* spritesheet;
    Sound* paddle_beep;
    Sound* edge_beep;
    Sound* point_beep;
    Sprite* background;
    Sprite* middle_line;
    Ball* ball;
    Player* player;
    Opponent* opponent;
    Border* edge_top;
    Border* edge_bottom;
    Border* edge_left;
    Border* edge_right;
    Scoreboard* player_scoreboard;
    Scoreboard* opponent_scoreboard;

    void update_entities();
    void draw();
};

#endif 
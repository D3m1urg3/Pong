// Pong - Yonatan Calderon 2017

#include "game.h"
#include "globals.h"

#define MS_PER_FRAME 33 // 30 fps

long get_current_time();
void sleep(long ms);

int main(int argc, char **argv)
{
    // Init
    srand(time(NULL)); 
    Game game;

    // Game loop
    if (game.init_ok())
    {
        while (game.get_state() != FINISHED)
        {
            long start_time = get_current_time();
            game.update();
            sleep(start_time + MS_PER_FRAME - get_current_time());
        }
    }

    return 0;
}

// Game loop functions 
long get_current_time()
{
    SYSTEMTIME time;
    GetSystemTime(&time);
    LONG time_ms = (time.wSecond * 1000) + time.wMilliseconds;

    return time_ms;
}

void sleep(long ms)
{
    SDL_PumpEvents();
    SDL_Delay(ms);
    //Sleep(ms); old code. Had to use SDL functions to avoid freezing
}



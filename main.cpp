// Pong Clon - Yonatan Calderon 2017

#include "graphics.h"
#include "globals.h"

#define MS_PER_FRAME 33 // 30 fps

void input();
void update();
void render();
long get_current_time();
void sleep(long ms);

int main()
{
    // Init
    // ...

    // Game loop
    while (true)
    {
        long start_time = get_current_time();
        input();
        update();
        render();
        sleep(start_time + MS_PER_FRAME - get_current_time());
    }

    return 0;
}

// Game loop functions 
void input()
{
}

void update()
{
}

void render()
{
}

long get_current_time()
{
    SYSTEMTIME time;
    GetSystemTime(&time);
    LONG time_ms = (time.wSecond * 1000) + time.wMilliseconds;

    return time_ms;
}

void sleep(long ms)
{
    Sleep(ms);
}



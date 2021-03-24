#include "input.h"
#include "SDL.h"
#include "log.h"

Input::Input()
{
}

Input::~Input()
{
}

Controls Input::check_for_input()
{
    SDL_Event ev;
    Controls controls = NONE;
    while (SDL_PollEvent(&ev))
    {
        switch (ev.type)
        {
        case SDL_KEYDOWN:
            switch (ev.key.keysym.sym)
            {
            case SDLK_UP:
                controls = UP;
                break;
            case SDLK_DOWN:
                controls = DOWN;
                break;
            case SDLK_w:
                controls = UP;
                break;
            case SDLK_s:
                controls = DOWN;
                break;
            case SDLK_ESCAPE:
                controls = END;
                break;
            default:
                controls = NONE;
                break;
            }
            break;
        case SDL_KEYUP:
            controls = NONE;
            break;
        }
    }
    return controls;
}
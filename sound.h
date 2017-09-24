#ifndef __SOUND__
#define __SOUND__

#include "SDL_mixer.h"
#include "globals.h"

bool init_sound();

class Sound
{
public:
    Sound(std::string wav_fullfilename);
    ~Sound();

    void play();

private:
    Mix_Chunk* sound;
};

#endif

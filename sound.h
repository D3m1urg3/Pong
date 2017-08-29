#ifndef __SOUND__
#define __SOUND__

#include "SDL_mixer.h"

bool init_sound();

class Sound
{
public:
    Sound(const char* wav_fullfilename);
    ~Sound();

    void play();

private:
    Mix_Chunk* sound;
};

#endif

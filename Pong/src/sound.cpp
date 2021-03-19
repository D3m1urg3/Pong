#include "sound.h"

bool init_sound()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        return false;
    }
    return true;
}

Sound::Sound(std::string wav_fullfilename)
    :sound(nullptr)
{
    sound = Mix_LoadWAV(wav_fullfilename.c_str());
}

Sound::~Sound()
{
    Mix_FreeChunk(sound);
}

void Sound::play()
{
    if (sound != nullptr)
    {
        Mix_PlayChannel(-1, sound, 0);
    }
}
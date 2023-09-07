#ifndef MUSIC_H
#define MUSIC_H

#include <string>
#include <SDL_mixer.h>

class Music {
public:
    //Construtor
    Music();
    Music(std::string file);
    // Funções
    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(std::string file);
    bool IsOpen();

private:
    //Ponteiros 
    Mix_Music* music;
};
#endif
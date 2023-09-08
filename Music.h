#ifndef MUSIC_H
#define MUSIC_H

#include <string>
#include <SDL_mixer.h>

class Music {
public:
    // Construtores e Destrutor
    Music();
    Music(const std::string& file);
    ~Music();

    // Métodos públicos
    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(const std::string& file);
    bool IsOpen() const;

private:
    // Atributos privados
    Mix_Music* music;
};

#endif
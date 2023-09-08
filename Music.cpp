#include "Music.h"
#include <iostream>
#include <SDL_mixer.h>

Music::Music() : music(nullptr) {
}

Music::Music(const std::string& file) : music(nullptr) {
    Open(file);
}

void Music::Play(int times) {
    if (music != nullptr) {
        Mix_PlayMusic(music, times);
    }
}

void Music::Stop(int msToStop) {
    if (music != nullptr) {
        Mix_FadeOutMusic(msToStop);
    }
}

void Music::Open(const std::string& file) {
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        std::cerr << "Erro ao carregar música: " << Mix_GetError() << std::endl;
    }
}

bool Music::IsOpen() const {
    if (music != nullptr){
        return true;
    }else{
        return false;
    }
}

Music::~Music() {
    Stop(1500);
    if (music != nullptr) {
        Mix_FreeMusic(music);
        music = nullptr;
        
    }
}
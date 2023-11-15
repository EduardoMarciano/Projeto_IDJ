#include <iostream>
#include "../Headers/Music.h"
#include "../Headers/Resources.h"

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
    music = Resources::GetMusic(file.c_str()).get();
    if (music == nullptr) {
        music = Resources::GetMusic(file.c_str()).get();

        if(music == nullptr){ 
            std::cerr << "Erro ao carregar música: " << Mix_GetError() << std::endl;
        }
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

}
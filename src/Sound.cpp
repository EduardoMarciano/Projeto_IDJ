#include <iostream>
#include "../Headers/Sound.h"
#include "../Headers/Resources.h"

Sound::Sound(GameObject& associated) :Component(associated), chunk(nullptr) {

}
Sound::Sound(GameObject& associated, std::string file) : Sound(associated){
    Open(file);
}
Sound::~Sound(){

}
void Sound::Play(int times){
    Mix_PlayChannel(-1,chunk, times-1);

}
void Sound::Stop(){
    if (chunk != nullptr) {
        Mix_HaltChannel(-1);
    }
}
void Sound::Open(std:: string file){
    chunk = Resources::GetSound(file.c_str()).get();

    if (chunk == nullptr){
        chunk = Resources::GetSound(file.c_str()).get();
        if(chunk == nullptr){
                   std::cout << "Could not open file: " << SDL_GetError() << std::endl;
        }
    }
}
void Sound::Update(float dt){

}
void Sound::Render(){

}

bool Sound::IsOpen() {
    if (chunk != nullptr){
        return true;
    }else{
        return false;
    }
}

bool Sound::Is(std::string type) {
    if (type == "Sound"){
        return true;
    }
    return false;
}
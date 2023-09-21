#include <iostream>
#include "../Headers/Sound.h"

Sound::Sound(GameObject& associated) :Component(associated), chunk(nullptr) {

}
Sound::Sound(GameObject& associated, std::string file) : Sound(associated){
    Open(file);
}
Sound::~Sound(){
    if(chunk != nullptr){
        Stop();
        Mix_FreeChunk(chunk);
    }
}
void Sound::Play(int times){
    Mix_PlayChannel(-1,chunk, times-1);

}
void Sound::Stop(){
    if (chunk != nullptr) {
        Mix_HaltChannel(-1);
    }
}
void Sound::Open(std:: string file)
{
    chunk = Mix_LoadWAV(file.c_str());

    if (chunk == nullptr){
        printf("Could not open file: %s\n", SDL_GetError());
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
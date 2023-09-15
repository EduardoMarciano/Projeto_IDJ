#include <iostream>
#include "Component.h"
#include "GameObject.h"
#include "Sound.h"

Sound::Sound(GameObject& associated) :Component(associated), chunk(nullptr) {

}
Sound::Sound(GameObject& associated, std::string file) : Sound(associated){
    Open(file);

}
Sound::~Sound(){
    if(){}
    void Mix_FreeChunk(Mix_Chunk* chunk);

}
void Sound::Play(int times){

}
void Sound::Stop(){

}
void Sound::Open(std::string file){

}
void Sound::Update(float dt){

}
void Sound::Render(){

}
bool Sound::IsOpen(){
    
    return false;
}
bool Sound::Is(std::string type){
    
    return true;
}
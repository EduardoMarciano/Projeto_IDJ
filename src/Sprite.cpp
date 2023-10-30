#include <iostream>
#include <SDL_image.h>
#include "../Headers/Game.h"
#include "../Headers/Sprite.h"
#include "../Headers/Camera.h"
#include "../Headers/Resources.h"


Sprite::Sprite(GameObject& associated) : Component(associated), texture(nullptr) {
    associated.box.h = height;
    associated.box.w = width;

}
Sprite::Sprite(const std::string file, GameObject& associated) : Component(associated), texture(nullptr) {
    Open(file);
}

Sprite::~Sprite() {

}

void Sprite::Open( const std::string file) {
    texture = Resources::GetImage(file.c_str());

    if (texture == nullptr) {
         texture = Resources::GetImage(file.c_str());
         if(texture == nullptr){
             std::cerr << "Erro ao carregar textura: " << SDL_GetError() << std::endl;
        return;
         }
    }
    int queryResult = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);   
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
    
}

void Sprite::Render() {
    Sprite::Render(associated.box.x, associated.box.y);
}

void Sprite::Render(int x, int y){
    SDL_Rect dstLoc = {x + (int)Camera::pos.x, y + (int)Camera::pos.y, clipRect.w, clipRect.h};
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstLoc, 
    associated.rotationAngle, nullptr, SDL_FLIP_NONE);   
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

void Sprite::Update(float teste) {
}

bool Sprite::IsOpen() {
    if(texture != nullptr){
        return true;
    }else{
        return false;
    }
}

bool Sprite::Is( std::string type)  {
    if (type == "Sprite"){
        return true;
    }
    return false;
}
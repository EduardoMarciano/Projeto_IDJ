#include <iostream>
#include <cmath>
#include <SDL_image.h>
#include "../Headers/Game.h"
#include "../Headers/Sprite.h"
#include "../Headers/Camera.h"
#include "../Headers/Resources.h"

Sprite::Sprite(GameObject& associated) : Component(associated), texture(nullptr), scale(1,1), height(0), width(0){
}
Sprite::Sprite(const std::string file, GameObject& associated) : Sprite(associated) {
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
    
    SetClip(0, 0, GetWidth(), GetHeight());
    associated.box.h = GetHeight();
    associated.box.w = GetWidth();
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render() {
    SDL_Rect dstrect = {(int)associated.box.x + (int)Camera::pos.x,(int) associated.box.y + (int)Camera::pos.y,(int) associated.box.w,(int) associated.box.h};
    double degress = associated.rotationAngle * (180.0f / M_PI);
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect, 
    degress, nullptr, SDL_FLIP_NONE); 
}

void Sprite::Render(int x, int y){
    SDL_Rect dstrect = {x + (int)Camera::pos.x, y + (int)Camera::pos.y, clipRect.w, clipRect.h};
    double degress = associated.rotationAngle * (180.0f / M_PI);
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect, 
    degress, nullptr, SDL_FLIP_NONE);   
}

int Sprite::GetWidth() {
    return (width)*scale.x;
}

int Sprite::GetHeight() {
    return (height)*scale.y;
}

void Sprite::SetScale(float scaleX, float scaleY){
    if (scaleX > 0){
        this->scale.x = scaleX;
        associated.box.w = associated.box.w * scale.x;
    }
    if (scaleY > 0){
        this->scale.y = scaleY;
        associated.box.h = associated.box.h * scale.y;
    }
}

void Sprite::Update(float teste) {
}

bool Sprite::IsOpen() {
    return (texture != nullptr);
}

bool Sprite::Is( std::string type)  {
    return(type == "Sprite");
}
#include "Sprite.h"
#include <iostream>
#include <SDL_image.h>
#include "Game.h"

Sprite::Sprite(GameObject& associated) : Component(associated), texture(nullptr) {

}
Sprite::Sprite(const std::string& file, GameObject& associated) : Component(associated), texture(nullptr) {
    Open(file);
}

Sprite::~Sprite() {
    if (texture != nullptr){
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(const std::string& file) {
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

    if (texture == nullptr) {
        std::cerr << "Erro ao carregar textura: " << SDL_GetError() << std::endl;
        return;
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

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    
    SDL_Rect* srcrect;
    SDL_Rect* dstrect;

    dstrect->x = associated.box.x;
    dstrect->y = associated.box.y;
    dstrect->w = associated.box.w;
    dstrect->h = associated.box.h;

    SDL_RenderCopy(renderer, texture, srcrect, dstrect);
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

void Sprite::Update(float teste) {
    return;
}

bool Sprite::IsOpen() {
    if(texture != nullptr){
        return true;
    }else{
        return false;
    }
}

bool Sprite::Is( std::string type)  {
    return type == "Sprite";
}
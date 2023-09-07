#include "Sprite.h"
#include <iostream>
#include <SDL_image.h>
#include "Game.h"

Sprite::Sprite() : texture(nullptr) {

}

 Sprite::Sprite(const std::string& file): texture(nullptr) {
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

void Sprite::Render(int x, int y) {

    SDL_Renderer* renderer = Game::GetInstance().GetRenderer();
    
    SDL_Rect* srcrect;
    SDL_Rect* dstrect;

    dstrect->x = x;
    dstrect->y = y;
    dstrect->w = clipRect.w;
    dstrect->h = clipRect.h;

    SDL_RenderCopy(renderer, texture, srcrect, dstrect);
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    if(texture != nullptr){
        return true;
    }else{
        return false;
    }
}
#include "Sprite.h"

Sprite::Sprite() : texture(nullptr) {

}

Sprite::Sprite(string file) : texture(nullptr) {
    Open();

}

Sprite::~Sprite() {
    if (SDL_Texture* != nullptr){
        SDL_DestroyTexture(SDL_Texture*);
    }
}

void Sprite::Open() {
    if(SDL_Texture* != nullptr){
        if (IMG_LoadTexture(SDL_Renderer* renderer, const char* path) == nullptr){
            std::cerr << "Erro ao abrir textura: " << SDL_GetError() << std::endl;
        }
        
        SDL_QueryTexture(SDL_Texture* texture, nullptr, nullptr, width&, height&);
        SetClip(x : int, y : int, w : int, h : int);
    }
}

void Sprite::SetCplip( int x, int y, int w, int h) {
    clipRect(x, y, w, h);

}

void Sprite::Render() {
    SDL_RenderCopy(SDL_Renderer* render, SDL_Texture* texture, SDL_Rect* srcrect, SDL_Rect* dstrect);
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    if(SDL_Texture* != nullptr){
        return true;
    }
}
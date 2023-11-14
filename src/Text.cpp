
#include <iostream>
#include "SDL_ttf.h"

#include "SDL_render.h"
#include "../Headers/Game.h"
#include "../Headers/Text.h"
#include "../Headers/Camera.h"
#include "../Headers/Resources.h"


Text::Text(GameObject& associated, std::string fontFile, int fontSize, 
           TextStyle style, std::string text, SDL_Color color) : Component(associated),
           font(nullptr), color(color) ,style(style), text(text), fontFile(fontFile), 
           fontSize(fontSize) ,texture(nullptr), elapsedTime(2){

    font = TTF_OpenFont(fontFile.c_str(), fontSize);
    RemakeTexture();
}

Text::~Text(){
    if(texture){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}
void Text::Update(float dt) {
    if (waiting) {
        waitTime -= 0.005;

        if (waitTime <= 0) {
            waiting = false;
            elapsedTime = blinkInterval;
        }
    } else {
        elapsedTime -= 0.0005;

        if (elapsedTime <= 0) {
            if (texture) {
                SDL_DestroyTexture(texture);
                texture = nullptr;
                waiting = true;
                waitTime = 1.0;
            } else {
                RemakeTexture();
                elapsedTime = blinkInterval; 
            }
        }
    }
}

void Text::Render(){
    if (elapsedTime > 0) {
        SDL_Rect clipRect = {0, 0,(int) associated.box.w,(int) associated.box.h};
        SDL_Rect destRect = {
            (int)(associated.box.x - Camera::pos.x),
            (int)(associated.box.y - Camera::pos.y),
            (int)associated.box.w,
            (int)associated.box.h
    };
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &destRect, 0, nullptr, SDL_FLIP_NONE);
    }
}

void Text::RemakeTexture() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    font = Resources::GetFont(fontFile, fontSize);
    if (!font) {
        return;
    }

    SDL_Surface* surface = nullptr;
    if (style == SOLID) {
        surface = TTF_RenderText_Solid(font, text.c_str(), color);
    } 
    else if (style == SHADED) {
        surface = TTF_RenderText_Shaded(font, text.c_str(), color, {0, 0, 0});
    } 
    else if (style == BLENDED) {
        surface = TTF_RenderText_Blended(font, text.c_str(), color);
    }

    if (!surface) {
        std::cerr << "Erro ao renderizar o texto: " << TTF_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Erro ao criar a textura a partir da surface." << std::endl;
        return;
    }

    int tempW, tempH;
    SDL_QueryTexture(texture, nullptr, nullptr, &tempW, &tempH);
    associated.box.h = tempH;
    associated.box.w = tempW;
}
    
void Text::SetText(std::string text) {
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
    this->fontSize = fontSize;
    RemakeTexture();
}
bool Text::Is(std::string type){
    return (type == "Text");
}
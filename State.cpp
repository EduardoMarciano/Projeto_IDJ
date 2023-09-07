#include "Sprite.h"
#include <iostream>
#include <SDL_image.h>
#include "Game.h"


State::State() : quitRequested(false){
    bg.Open("img/ocean.jpg");
}

void State::LoadAssets() {
}

void State::Update(float dt) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::Render() {
    bg.Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}
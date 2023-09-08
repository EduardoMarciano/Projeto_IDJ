#include "Sprite.h"
#include <iostream>
#include <SDL_image.h>
#include "Game.h"


State::State() : quitRequested(false), music("audio/stageState.ogg"){
    bg.Open("img/ocean.jpg");
    music.Play(-1);
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
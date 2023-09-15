#include "Sprite.h"
#include <iostream>
#include <SDL_image.h>
#include "Game.h"

State:: State(GameObject& bgObject) : quitRequested(false), music("audio/stageState.ogg"), bg(bgObject){
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
    bg.Render();
}

bool State::QuitRequested() {
    return quitRequested;
}
#include "State.h"

State::State() : quitRequested(false), bg() {

}

bool State::QuitRequested() {
    return quitRequested;
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

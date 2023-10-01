#include "../Headers/InputManager.h"
#include <SDL2/SDL.h>

InputManager::InputManager() : mouseX(0), mouseY(0), updateCounter(0), quitRequested(false) {
    for (int i = 0; i < 6; ++i) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }
}
InputManager::~InputManager(){
    keyState.clear();
	keyUpdate.clear();
}

void InputManager::Update() {
    SDL_Event event;
    SDL_GetMouseState(&mouseX, &mouseY);
    
    quitRequested = false;
    ++updateCounter;
    
    while (SDL_PollEvent(&event)) {
            if (!event.key.repeat) {

                switch (event.type) {
                    
                    case SDL_KEYDOWN: {
                        auto it = keyState.find(event.key.keysym.sym);
                        if (it != keyState.end()) {
                           	keyState[event.key.keysym.sym] = true;
				            keyUpdate[event.key.keysym.sym] = updateCounter;
                        }
                        break;
                    }
                    case SDL_KEYUP: {
                        auto it = keyState.find(event.key.keysym.sym);
                        if (it != keyState.end()) {
                            keyState[event.key.keysym.sym] = false;
				            keyUpdate[event.key.keysym.sym] = updateCounter;
                        }
                        break;
                    }

                    case SDL_MOUSEBUTTONDOWN:
                        mouseState[event.button.button - 1] = true;
                        mouseUpdate[event.button.button - 1] = updateCounter;
                        break;

                    case SDL_MOUSEBUTTONUP:
                        mouseState[event.button.button - 1] = false;
                        mouseUpdate[event.button.button - 1] = updateCounter;
                        break;

                    case SDL_QUIT:
                        quitRequested = true;
                        break;
                }
        }
    }
}

InputManager& InputManager::GetInstance(){
    static InputManager instance;
    return instance;
}

int InputManager::GetMouseX(){
    return mouseX;
    
}

int InputManager::GetMouseY(){
    return mouseY;
}
bool InputManager::KeyPress(int key) {
    return keyUpdate[key] == updateCounter && keyState[key];
}

bool InputManager::KeyRelease(int key) {
    return keyUpdate[key] == updateCounter && !keyState[key];
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::MousePress(int button) {
    return mouseUpdate[button - 1] == updateCounter && mouseState[button - 1];
}

bool InputManager::MouseRelease(int button) {
    return mouseUpdate[button - 1] == updateCounter && !mouseState[button - 1];
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button - 1];
}

bool InputManager::QuitRequested(){
    return quitRequested;

}
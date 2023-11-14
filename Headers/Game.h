#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <string>
#include <stack>
#include <memory>
#include "State.h"
#include "SDL_ttf.h"

class Game {
public:
    Game (std::string title, int width, int height);
    ~Game();

    void Run();
    void Push(State* state);

    void CleanupSDL();
    void InitializeSDL();
    
    int GetWidth();
    int GetHeight();
    
    float GetDeltaTime();    
    State& GetCurrentState();
    static Game& GetInstance();
    SDL_Renderer* GetRenderer();

private:

    float dt;
    int frameStart;
    int width;
    int height;

    State* storedState;
    SDL_Window* window;
    static Game* instance;
    SDL_Renderer* renderer;

    void CalculateDeltaTime();
    std::stack<std::unique_ptr<State>> stateStack;
};

#endif

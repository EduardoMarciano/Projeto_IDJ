#ifndef GAME_H
#define GAME_H

#include "State.h"
#include <SDL.h>
#include <string>

class Game {
public: 
    // Destrutor
    ~Game();
    // Função
    void Run();
    void CleanupSDL();
    void InitializeSDL();
    // Retorno de referênicas
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();

private:
    //Construtor
    Game(const std::string& title, int width, int height);
    //Ponteiros
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
};

#endif

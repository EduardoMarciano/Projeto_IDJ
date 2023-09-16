#include "Game.h"
#include "GameObject.h"
#include "State.h"
#include <iostream>
#include <SDL_image.h>
#include <SDL_mixer.h> 
#include <SDL_ttf.h>

Game* Game::instance = nullptr;

Game::Game(const std::string& title, int width, int height) {
    // cria ou reenvia a intanciação do jogo
    if (instance != nullptr) {
        std::cerr << "Erro: Já existe uma instância da classe Game em execução." << std::endl;
    } else {
        instance = this;
    }
    //Inicializa todas as dependências vinculadas a SDL
    InitializeSDL();

    //Criando a janela
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

    if (window == nullptr) {
        std::cerr << "Erro ao criar a janela: " << SDL_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //Criando o renderizador
    if (renderer == nullptr) {
        std::cerr << "Erro ao criar o renderizador: " << SDL_GetError() << std::endl;


    }
    GameObject gameObject;
    State* state = new State(gameObject);  
}

Game::~Game() {
    //Limpa a SDL   
    CleanupSDL();
}

void Game::Run() {
    while (!state->QuitRequested()) {
        state->Update(0.033f);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
}

Game& Game::GetInstance() {
    if(instance != nullptr){
        return *instance;
    
    }else{
        instance = new Game("Eduardo Marciano - 211055227", 1024, 600);
        return *instance;
    }
}

State& Game::GetState() {
    return *state;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

void Game::InitializeSDL() {

    //Inicializando as funcionalidades do SDL
    int resultadoSDL =  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);

    if (resultadoSDL != 0) {
        std::cerr << "Erro ao inicializar a biblioteca SDL: " << SDL_GetError() << std::endl;
    }
    //Inicializando as funcionalidaes da SDL_ Image
    int flagsIMG = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

    if (flagsIMG == (0)) {
        std::cerr << "Erro ao inicializar a biblioteca SDL_image: " << IMG_GetError() << std::endl;
    }
    //Inicializando as funcionalidades da SDL_Sounds
    int flagsMIX = Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG);

    if (flagsMIX == 0) {
        std::cerr << "Erro ao inicializar a biblioteca SDL_mixer: " << Mix_GetError() << std::endl;
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        std::cerr << "Erro ao abrir o áudio SDL_mixer: " << Mix_GetError() << std::endl;
    } else {
        Mix_AllocateChannels(32);
    }
}

void Game::CleanupSDL() {

    delete state;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
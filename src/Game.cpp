#include <iostream>
#include "../Headers/Game.h"
#include "../Headers/Resources.h"
#include "../Headers/InputManager.h"
#include "SDL_ttf.h"

Game* Game::instance = nullptr;

Game::Game(std::string title, int width, int height) : width(width), height(height), dt(0.0f), frameStart(0), 
    storedState(nullptr), window(nullptr), renderer(nullptr)  {
    
    if (Game::instance != nullptr) {
        std::cerr << "Erro: Já existe uma instância da classe Game em execução." << std::endl;
    } else {
        Game::instance = this;
    }
    //Inicializa todas as dependências vinculadas a SDL
    InitializeSDL();

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GetWidth(), GetHeight(), 0);
    if (window == nullptr) {
        std::cerr << "Erro ao criar a janela: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Erro ao criar o renderizador: " << SDL_GetError() << std::endl;
    }
    srand(time(NULL));
}

Game::~Game() {
    CleanupSDL();
}

void Game::Push(State *state){
    storedState = state;
}

void Game::Run() {
    if(storedState){
        stateStack.push((std::unique_ptr<State>)storedState);
        stateStack.top()->Start();
        storedState = nullptr;
    }
    while ((!stateStack.empty())) {
        
        if(stateStack.top()->QuitRequested()){
            break;
        }
        if(stateStack.top()->PopRequested()){
            stateStack.top()->Pause();
            stateStack.pop();
            
            if(!stateStack.empty()){
                stateStack.top()->Resume();
            }
        }
        if(storedState){
            if(!stateStack.empty()){
            stateStack.top()->Pause();
            }
            stateStack.push((std::unique_ptr<State>) storedState);
            stateStack.top()->Start();
            storedState = nullptr;
        }
        CalculateDeltaTime();
        stateStack.top()->Update(dt);
        InputManager::GetInstance().Update();
        stateStack.top()->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(dt);
    }
    Resources::ClearFonts();
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}

Game& Game::GetInstance() {
    if(instance != nullptr){
        return *instance;
    
    }else{
        instance = new Game("Eduardo Marciano - 211055227", 1024, 600);
        return *instance;
    }
}

State& Game::GetCurrentState() {
    return *stateStack.top();
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

    int resultadoTTF = TTF_Init();

    if(resultadoTTF != 0){
        std::cerr << "Erro ao iniciar a SDL_ttf: " << TTF_GetError() << std::endl;
    }

}

void Game::CleanupSDL() {
    if(storedState){
        delete storedState;
        storedState = nullptr;
    }
    while(!stateStack.empty()){
        stateStack.pop();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    Resources::ClearFonts();
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}

void Game::CalculateDeltaTime() {
    Uint32 frameEnd = SDL_GetTicks(); 
    Uint32 frameTicks = frameEnd - frameStart;
    frameStart = frameEnd;
    dt = static_cast<float>(frameTicks) / 1000.0f;
}

float Game::GetDeltaTime(){
    return dt;
}
int Game::GetHeight(){
    return this->height;
}

int Game::GetWidth(){
    return this->width;
}
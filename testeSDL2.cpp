#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

int main(int argc, char** argv) {

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "SDL inicializado com sucesso!" << std::endl;

    if ((IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) & (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)) != (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)) {
        std::cerr << "Erro ao inicializar SDL_image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    std::cout << "SDL_image inicializado com sucesso!" << std::endl;

    if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG) < 0) {
        std::cerr << "Erro ao inicializar SDL_mixer: " << Mix_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    std::cout << "SDL_mixer inicializado com sucesso!" << std::endl;

    if (TTF_Init() < 0) {
        std::cerr << "Erro ao inicializar SDL_ttf: " << TTF_GetError() << std::endl;
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    std::cout << "SDL_ttf inicializado com sucesso!" << std::endl;

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    std::cout << "Configuração realizada com sucesso!" << std::endl;

    return 0;
}
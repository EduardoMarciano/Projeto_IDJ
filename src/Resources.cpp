#include "../Headers/Game.h"
#include "../Headers/Resources.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <iostream>

std::unordered_map<std::string, SDL_Texture *> Resources::imageTable;
std::unordered_map<std::string, Mix_Music *> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk *> Resources::soundTable;
std::unordered_map<std::string, TTF_Font *> Resources::fontTable;

SDL_Texture* Resources::GetImage(std::string file){
    SDL_Texture* texture;

    auto pair = imageTable.find(file);
    if (pair != imageTable.end()){ 
        texture = pair->second;
        return texture;
    }else{
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        imageTable[file] = texture;
        return texture;
    }
}

Mix_Chunk* Resources::GetSound(std::string file){
    Mix_Chunk* chunk;

    auto pair = soundTable.find(file);
    if(pair != soundTable.end()){
        chunk = pair->second;
        return chunk;
    }else{
        chunk = Mix_LoadWAV(file.c_str());
        soundTable[file] = chunk;
        return chunk;

    }
}

Mix_Music* Resources::GetMusic(std::string file){
    Mix_Music* music;

    auto pair = musicTable.find(file);
    if(pair != musicTable.end()){
        music = pair->second;
        return music;
    }else{
        music = Mix_LoadMUS(file.c_str());
        musicTable[file] = music;
        return music;
    }
}

TTF_Font* Resources::GetFont(std::string file, int fontSize) {
        std::string key = file + std::to_string(fontSize);

        auto pair = fontTable.find(key);
        if (pair != fontTable.end()) {
            return pair->second;

        } else {
            TTF_Font* font = TTF_OpenFont(file.c_str(), fontSize);
            
            if (!font) {
                std::cerr << "Erro ao carregar a fonte: " << TTF_GetError() << std::endl;
                return nullptr;
            }
            fontTable[key] = font;

            return font;
        }
}

void Resources::ClearImages(){
    for (auto pair : imageTable) {
        SDL_Texture* texture = pair.second;
         SDL_DestroyTexture(texture);
    }
    imageTable.clear();
}
    
void Resources::ClearSounds(){
     for (auto pair : soundTable) {
        Mix_Chunk* chunk = pair.second;
        Mix_FreeChunk(chunk);
    }
     soundTable.clear();
}

void Resources::ClearMusics(){
     for (auto pair : musicTable) {
         Mix_Music* music = pair.second;
         Mix_FreeMusic(music);
    }  
    musicTable.clear();
}
void Resources::ClearFonts(){
    for (auto pair : fontTable) {
         TTF_Font* fonte = pair.second;
         TTF_CloseFont (fonte);
    }  
    fontTable.clear();
};

#ifndef Resources_H
#define Resources_H

#include <string>
#include <memory>
#include <iostream>
#include <unordered_map>

#include "SDL_ttf.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "../Headers/Game.h"

class Resources {
public:
    static std::shared_ptr<Mix_Chunk> GetSound(std::string file);
    static std::shared_ptr<Mix_Music> GetMusic(std::string file);
    static std::shared_ptr<SDL_Texture> GetImage(std::string file);
    static std::shared_ptr<TTF_Font> GetFont(std::string file, int fontNumber); 
    
    static void ClearSounds();
    static void ClearMusics();
    static void ClearImages(); 
    static void ClearFonts();
private:
    static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
    static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
    static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
};

#endif

#ifndef Resources_H
#define Resources_H

#include "SDL_ttf.h"
#include <string>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <unordered_map>

class Resources {
public:
    static Mix_Chunk* GetSound(std::string file);
    static Mix_Music* GetMusic(std::string file);
    static SDL_Texture* GetImage(std::string file);
    static TTF_Font* GetFont(std::string file, int fontNumber); 
    
    static void ClearSounds();
    static void ClearMusics();
    static void ClearImages(); 
    static void ClearFonts();
private:
    static std::unordered_map<std::string, TTF_Font*> fontTable;
    static std::unordered_map<std::string, Mix_Chunk*> soundTable;
    static std::unordered_map<std::string, Mix_Music*> musicTable;
    static std::unordered_map<std::string, SDL_Texture*> imageTable;
};

#endif

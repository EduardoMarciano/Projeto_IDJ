#include "../Headers/Resources.h"

std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;


std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
    auto it = imageTable.find(file);

    if (it != imageTable.end()) {
        return it->second;
    } else {
        SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

        if (texture == nullptr) {
            std::cerr << "Erro ao carregar textura: " << SDL_GetError() << std::endl;
            return nullptr;
        }

        std::shared_ptr<SDL_Texture> sharedTexture(texture, [](SDL_Texture* texture) {
            SDL_DestroyTexture(texture);
        });

        imageTable[file] = sharedTexture;
        return sharedTexture;
    }
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
    auto it = soundTable.find(file);

    if (it != soundTable.end()) {
        return it->second;
    } else {
        Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());

        if (!chunk) {
            std::cerr << "Erro ao carregar som: " << Mix_GetError() << std::endl;
            return nullptr;
        }

        std::shared_ptr<Mix_Chunk> sharedChunk(chunk, [](Mix_Chunk* chunk) {
            Mix_FreeChunk(chunk);
        });

        soundTable[file] = sharedChunk;
        return sharedChunk;
    }
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
    auto it = musicTable.find(file);

    if (it != musicTable.end()) {
        return it->second;
    } else {
        Mix_Music* music = Mix_LoadMUS(file.c_str());

        if (!music) {
            std::cerr << "Erro ao carregar música: " << Mix_GetError() << std::endl;
            return nullptr;
        }

        std::shared_ptr<Mix_Music> sharedMusic(music, [](Mix_Music* music) {
            Mix_FreeMusic(music);
        });

        musicTable[file] = sharedMusic;
        return sharedMusic;
    }
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int fontSize) {
    std::string key = file + std::to_string(fontSize);
    auto it = fontTable.find(key);

    if (it != fontTable.end()) {
        return it->second;
    } else {
        TTF_Font* font = TTF_OpenFont(file.c_str(), fontSize);

        if (!font) {
            std::cerr << "Erro ao carregar a fonte: " << TTF_GetError() << std::endl;
            return nullptr;
        }

        std::shared_ptr<TTF_Font> sharedFont(font, [](TTF_Font* font) {
            TTF_CloseFont(font);
        });

        fontTable[key] = sharedFont;
        return sharedFont;
    }
}

void Resources::ClearImages() {
    auto it = imageTable.begin();
    while (it != imageTable.end()) {
        if (it->second.use_count() == 1) {
            it = imageTable.erase(it);
        } else {
            ++it;
        }
    }
}
    
void Resources::ClearSounds() {
    auto it = soundTable.begin();

    while (it != soundTable.end()) {
        if (it->second.use_count() == 1) {
            it = soundTable.erase(it);
        } else {
            ++it;
        }
    }
}

void Resources::ClearMusics() {
    auto it = musicTable.begin();

    while (it != musicTable.end()) {
        if (it->second.use_count() == 1) {
            it = musicTable.erase(it);
        } else {
            ++it;
        }
    }
}
void Resources::ClearFonts() {
    auto it = fontTable.begin();

    while (it != fontTable.end()) {
        if (it->second.use_count() == 1) {
            it = fontTable.erase(it);
        } else {
            ++it;
        }
    }
}
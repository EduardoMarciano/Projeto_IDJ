#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL.h>

class Sprite {
public:
    // Construtores e Destrutor
    Sprite();
    Sprite(const std::string& file);
    ~Sprite();

    // Métodos públicos
    void Open(const std::string& file);
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();

private:
    // Atributos privados
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
};

#endif

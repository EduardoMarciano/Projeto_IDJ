#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL.h>      
#include "State.h"    

class Sprite {
public:
    //Construtor
    State();
    State(string file);

    //Destrutor
    ~State();
    // Funções
    void SetClip(int x, int y, int w, int h);
    void Render(int x, int y);
    int  GetWidth();
    int  GetHeight();
    bool IsOpen();

private:
    //Ponteiros
    SDL_Texture*texture;
    int width;
    int height;
    SDL_Rect clipRect;
};
#endif
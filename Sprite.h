#ifndef SPRITE_H
#define SPRITE_H

#include "Component.h"
#include <string>
#include <SDL.h>

class Sprite : public Component {
public:
    // Construtores e Destrutor
    Sprite(GameObject& associated);
    Sprite(std::string& file, GameObject& associated);
    ~Sprite();

    // Métodos públicos
    void Open(std::string& file);
    void SetClip(int x, int y, int w, int h);
    int GetWidth();
    int GetHeight();
    bool IsOpen();

    //Metodos Herdados de Component
    void Render();
    void Update(float dt);
    bool Is(std::string type);

private:
    // Atributos privados
    int width;
    int height;
    SDL_Rect clipRect;
    SDL_Texture* texture;
};

#endif

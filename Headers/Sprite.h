#ifndef SPRITE_H
#define SPRITE_H

#include "Component.h"

class Sprite : public Component {
public:
    // Construtores e Destrutor
    Sprite(GameObject& associated);
    Sprite(const std::string file, GameObject& associated);
    ~Sprite();

    // Métodos públicos
    void Open(const std::string file);
    void SetClip(int x, int y, int w, int h);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    void Render(int x, int y);
    
    Vec2 GetScale ();
    void SetScale(float scaleX, float scaleY);

    //Metodos Herdados de Component
    void Render();
    void Update(float dt);
    bool Is(std::string type);

private:
    // Atributos privados
    int width;
    int height;
    Vec2 scale;
    SDL_Rect clipRect;
    std::shared_ptr<SDL_Texture> texture;
};

#endif

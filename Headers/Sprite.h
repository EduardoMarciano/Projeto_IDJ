#ifndef SPRITE_H
#define SPRITE_H

#include "Component.h"

class Sprite : public Component {
public:
    // Construtores e Destrutor
    Sprite(GameObject& associated);
    Sprite(const std::string file, GameObject& associated, int frameCount = 1, int currentFrame = 0, float frameTime = 0 , float timeElapsed = 0);
    ~Sprite();

    // Métodos públicos
    void Open(const std::string file);
    void SetClip(int x, int y, int w, int h);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    void Render(int x, int y);
    
    Vec2 GetScale ();
    void SetFrame (int frame);
    void SetFrameTime (float frameTime);
    void SetFrameCount (int frameCount);


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

    int frameCount;
    int currentFrame;
    float frameTime;
    float timeElapsed;

    SDL_Rect clipRect;
    std::shared_ptr<SDL_Texture> texture;
};

#endif

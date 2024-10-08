#ifndef Text_h
#define Text_h

#include "Component.h"
#include "GameObject.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include <string>

enum TextStyle {SOLID, SHADED, BLENDED};

class Text : public Component {
public:
    Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
    ~Text();
    
    void Render();
    void Update(float dt);
    bool Is(std::string type);

    void SetText(std::string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFontSize(int fontSize);
    void SetFontFile(std::string fontFile);

private:
    void RemakeTexture();
    int fontSize;

    bool waiting = false; 
    float waitTime = 2.0F;
    float elapsedTime = 2.0F;
    float blinkInterval = 2.0F;

    TTF_Font* font;
    SDL_Color color;
    TextStyle style;
    std::string text;
    std::string fontFile;
    SDL_Texture* texture;
};

#endif

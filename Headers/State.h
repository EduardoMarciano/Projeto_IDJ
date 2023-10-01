#ifndef STATE_H
#define STATE_H

#include "Sprite.h"
#include "Music.h"

class State {
public:
    State();
    ~State();

    // Funções
    bool QuitRequested();
    void Update(float dt);
    void Render();
    void LoadAssets();
private:
    void AddObject(int mouseX, int mouseY);

    Sprite* bg;
    Music* music;
    bool quitRequested;
    std::vector<std::unique_ptr<GameObject>> objectArray;
};

#endif

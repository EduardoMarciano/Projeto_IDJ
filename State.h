#ifndef STATE_H
#define STATE_H

#include <vector>
#include "Sprite.h"
#include "Music.h"

class State {
public:
    //Construtor
    State();
    // Funções
    bool QuitRequested();
    void LoadAssets();
    void Update( float dt);
    void Render();

private:
    Sprite bg;
    Music music;
    bool quitRequested;
};

#endif

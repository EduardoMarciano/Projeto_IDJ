#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>
#include "Sprite.h"
#include "Music.h"
#include "GameObject.h"

class State {
public:
    State(GameObject& bgObject);
    ~State();

    // Funções
    bool QuitRequested();
    void Update(float dt);
    void Render();
    void LoadAssets();
private:
    void Input();
    void AddObject(int mouseX, int mouseY);

    Sprite bg;
    Music music;
    bool quitRequested;
    std::vector<std::unique_ptr<GameObject>> objects;
};

#endif

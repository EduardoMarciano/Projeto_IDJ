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
    void Start();
    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
private:
    void AddObject(int mouseX, int mouseY);

    Sprite* bg;
    Music* music;
    bool started;
    bool quitRequested;
    std::vector< std::shared_ptr<GameObject>> objectArray;
};

#endif

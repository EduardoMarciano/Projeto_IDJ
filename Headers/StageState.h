#ifndef STAGESTATE_H
#define STAGESTATE_H

#include "Music.h"
#include "State.h"

class StageState : public State {
public:
    StageState();
    ~StageState();

    void Start();
    void Pause();
    void Resume();
    void Render();
    void LoadAssets();
    void Update(float dt);

private:
    Music* backgroundMusic;
    bool started;
    bool quitRequested;
    std::vector< std::shared_ptr<GameObject>> objectArray;
};

#endif
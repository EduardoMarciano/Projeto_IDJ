#ifndef STAGESTATE_H
#define STAGESTATE_H

#include "Music.h"
#include "State.h"
#include "Game.h"

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
};

#endif
#ifndef STAGESTATE_H
#define STAGESTATE_H

#include "Music.h"
#include "State.h"

class StageState : State {
public:
    StageState();
    ~StageState();

    void Start();
    void Pause();
    void Resume();
    void Render();
    void Update(float dt);

private:
    Music* music;
    bool started;
    bool quitRequested;
    std::vector< std::shared_ptr<GameObject>> objectArray;
};

#endif
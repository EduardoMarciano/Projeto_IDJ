#ifndef END_STATE_H
#define END_STATE_H
#include "Text.h"
#include "State.h"
#include "Music.h"
#include "GameObject.h"
#include "GameObject.h"
#include "TitleState.h"
#include "StageState.h"
#include <cfloat>

class EndState : public State {
public:
    EndState();
    ~EndState();

    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
private:
    Music* backgroundMusic;
};

#endif

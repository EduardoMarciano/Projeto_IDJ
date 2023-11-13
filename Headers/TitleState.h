#ifndef TitleState_h
#define TitleState_h

#include "State.h"
#include "Game.h"
#include "Sprite.h"
#include "GameObject.h"
#include "StageState.h"
#include "InputManager.h"

class TitleState : public State {
    public:
        TitleState();
        ~TitleState();

        void Render();
        void Update(float dt);
        void LoadAssets();
        
        void Pause();
        void Start();
        void Resume();
    private:


};

#endif
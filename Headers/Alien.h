#ifndef Alien_H
#define Alien_H

#include "Component.h"
#include "InputManager.h"
#include "Sprite.h"
#include <string>
#include <vector>
#include <queue>

enum ActionType {MOVE, SHOOT};

class Alien: public Component{
    public:
        Alien (GameObject& associated, int nMinions);
        ~Alien ();

        void Start();
        void Update (float dt);
        void Render ();

        bool Is (std::string type);
    
    private:
        
        class Action {
            public:
                Action(ActionType type, float x, float y);
                ActionType type;
                Vec2 pos;
        };

        Vec2 speed;
        int hp;
        std::queue<Action> taskQueue;
        std::vector<std::weak_ptr<GameObject>> minionArray;
};

#endif
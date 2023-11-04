#ifndef Minion_h
#define Minion_h
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

class Minion : public Component{
    public:
        Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
        void Update(float dt);
        void Render();
        void Shoot(Vec2 target);

        bool Is(std::string type);
    
    private:
        float arc;
        float radius;
        std::weak_ptr<GameObject> alienCenter;
};

#endif
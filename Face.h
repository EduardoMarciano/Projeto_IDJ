#ifndef Face_H
#define Face_H

#include "Component.h"
#include "GameObject.h"
#include <SDL.h>
#include <string>

class Face: public Component{
    public:
        Face(GameObject& associated);
        
        void Damage(int Damage);
        void Update(float dt);
        void Render();

        bool Is(std::string type);


    private:
        int hitpoints;

};
#endif
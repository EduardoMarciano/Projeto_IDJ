#ifndef Face_H
#define Face_H

#include "Component.h"

class Face: public Component{
    public:
        Face(GameObject& associated);
        ~Face();
        
        void Damage(int Damage);
        void Update(float dt);
        void Render();

        bool Is(std::string type);


    private:
        int hitpoints;

};
#endif
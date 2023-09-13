#ifndef Component_H
#define Component_H

#include <SDL.h>
#include <string>
#include "Component.h"

class GameObject{
    public:
        GameObject();
        ~GameObject();

        //Public Methods
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component *cpt);
        void RemoveComponent(Component *cpt):
        Component GetComponent(std::string type);

        Rect box;
        //Public Atributes
    private:
        std::vector <Component*> components;
        bool isDead;

};

#endif
#ifndef GameObject_H
#define GameObject_H

#include <SDL.h>
#include <string>
#include <vector>
#include <memory>
#include "Rect.h"

class Component;

class GameObject {
public:
    GameObject();
    ~GameObject();

    // Public Methods
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(std::unique_ptr<Component> cpt);
    void RemoveComponent(std::unique_ptr<Component> cpt);
    std::unique_ptr<Component> GetComponent(std::string type);

    Rect box;

private:
    std::vector<std::unique_ptr<Component>> components; 
    bool isDead;
};

#endif

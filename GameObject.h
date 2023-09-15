#ifndef GameObject_H
#define GameObject_H

#include <SDL.h>
#include <string>
#include <vector>
#include <memory> // Adicione a inclusão para unique_ptr
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
    void AddComponent(std::unique_ptr<Component> cpt); // Alteração aqui
    void RemoveComponent(Component* cpt);
    Component* GetComponent(std::string type);

    Rect box;

private:
    std::vector<std::unique_ptr<Component>> components; // Alteração aqui
    bool isDead;
};

#endif

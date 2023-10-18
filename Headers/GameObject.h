#ifndef GameObject_H
#define GameObject_H


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
    void Start();
    void RequestDelete();
    
    void AddComponent(std::shared_ptr<Component> cpt);
    void RemoveComponent(std::shared_ptr<Component> cpt);
    std::shared_ptr<Component> GetComponent(std::string type);

    Rect box;
    bool started;

private:
    std::vector<std::shared_ptr<Component>> components;
    bool isDead;
};

#endif

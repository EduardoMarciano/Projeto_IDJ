#include <iostream>
#include "Component.h"
#include "GameObject.h"
#include <algorithm>


GameObject::GameObject() : box(0, 0, 0, 0), isDead(false) {

}

GameObject::~GameObject() {
    // Não é necessário fazer nada aqui, pois os unique_ptr cuidarão da liberação automática de memória.
}

void GameObject::Update(float dt) {
    for (auto& component : components) {
        component->Update(dt);
    }
}

void GameObject::Render() {
    for (auto& component : components) {
        component->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(std::unique_ptr<Component> cpt) {
    components.push_back(std::move(cpt)); // Usamos std::move para transferir a propriedade do ponteiro exclusivo
}

void GameObject::RemoveComponent(Component* cpt) {
    auto it = std::remove_if(components.begin(), components.end(),
        [cpt](const std::unique_ptr<Component>& component) {
            return component.get() == cpt;
        });

    if (it != components.end()) {
        components.erase(it, components.end());
    }
}

Component* GameObject::GetComponent(std::string type) {
    for (const auto& component : components) {
        if (component->Is(type)) {
            return component.get();
        }
    }
    return nullptr;
}

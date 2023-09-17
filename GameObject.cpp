#include <iostream>
#include "Component.h"
#include "GameObject.h"
#include <algorithm>


GameObject::GameObject() : box(0, 0, 0, 0), isDead(false) {

}

GameObject::~GameObject() {
    components.clear();
}

void GameObject::Update(float dt) {
    for (std::unique_ptr<Component>& component : components) {
        component->Update(dt);
    }
}

void GameObject::Render() {
    for (std::unique_ptr<Component>& component : components) {
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
    components.push_back(std::move(cpt));
}

void GameObject::RemoveComponent(std::unique_ptr<Component> cpt) {
        for (auto it = components.begin(); it != components.end(); ++it) {
            if (it->get() == cpt.get()) {
                components.erase(it);
                break;
            }
        }
}

std::unique_ptr<Component> GameObject::GetComponent(std::string type) {
    for (auto& component : components) {
        if (component->Is(type)) {
            return std::move(component);
        }
    }
    return nullptr;
}
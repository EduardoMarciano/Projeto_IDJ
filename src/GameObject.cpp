#include "../Headers/Component.h"

GameObject::GameObject() : box(0, 0, 0, 0), isDead(false), started(false) {

}

GameObject::~GameObject() {
    for (std::vector<int>::size_type i = components.size(); i > 0; i--){
        components.erase(components.begin() + i);
    }

    components.clear();
}

void GameObject::Update(float dt) {
    for (std::vector<int>::size_type i = 0; i < components.size(); i++){
        components[i]->Update(dt);
    }
}

void GameObject::Render() {
    for (std::vector<int>::size_type i = 0; i < components.size(); i++){
        components[i]->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(std::shared_ptr<Component> cpt){
    components.emplace_back(cpt);
    if (started) {
        cpt->Start();
    }
}

void GameObject::RemoveComponent(std::shared_ptr<Component> cpt){
    for (std::vector<int>::size_type i = 0; i < components.size(); i++){
        if (components[i] == cpt){
            components.erase(components.begin() + i);
        }
    }
}

std::shared_ptr<Component> GameObject::GetComponent(std::string type){
    for (std::vector<int>::size_type i = 0; i < components.size(); i++){
        if (components[i]->Is(type))
        {
            return components[i];
        }
    }

    return nullptr;
}

void GameObject::Start(){
    for (auto& component : components){
        component->Start();
    }
    started = true;
}   
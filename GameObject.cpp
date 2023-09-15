#include <iostream>
#include "Component.h"
#include "GameObject.h"

GameObject::GameObject(): isDead(false){

}

GameObject::~GameObject(){

    for(int i = components.size() -1; i >= 0; i--){
        delete components[i]; 
    }
    components.clear();
}

void GameObject::Update(float dt){

    for(Component* i : components){
        i->Update(dt);
    }
}

void GameObject::Render(){
    for(Component*i : components){
        i->Render();
    }
}

bool GameObject::IsDead(){
    return isDead;
}

void GameObject::RequestDelete(){
    isDead = true;
}

void GameObject::AddComponent(Component *cpt){
    
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {

    int contador = -1;
    for (Component* componente : components) {
        
        if (componente == cpt) {
            delete componente; // Libere a memória do componente
            components.erase( components.begin() + contador);
            break; // Saia do loop assim que encontrar o componente
        }
        contador++;
    }
}

Component* GameObject::GetComponent(std::string type){
    for(Component* componente : components ){
        if (componente->Is(type)){
            return componente;
        }
    }
    return nullptr;
}
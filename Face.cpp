#include <iostream>
#include "Component.h"
#include "GameObject.h"
#include "Face.h"
#include "Sound.h"

Face::Face(GameObject& associated):Component(associated), hitpoints(30){

}
Face::~Face(){

}

void Face::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        associated.RequestDelete();
}
}


void Face::Update(float dt){

}

void Face::Render(){

}

bool Face::Is(std::string type) {
    return type == "Face";
}

#include "Component.h"
#include "Rect.h"

Component::Component(GameObject& associated) : associated(associated) {
    
}
Component::~Component(){

}

void Component::Update(float dt){

}

bool Component::Is(std::string type){
    return type == "Component";
}

void Component::Render(){
    return;
}
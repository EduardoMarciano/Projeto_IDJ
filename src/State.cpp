#include "../Headers/State.h"

State::State() : popRequested(false), quitRequested(false), started(false){

}

State::~State(){
    objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject *go){
    std::shared_ptr<GameObject> shared_version(go);

    objectArray.push_back(shared_version);
    if (started){
        shared_version->Start();
    }
    std::weak_ptr <GameObject> weak_version(shared_version);

    return weak_version;

}
 std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go){
    for(auto& object : objectArray){
        if(go == object.get()){
            std::weak_ptr <GameObject> weak_version(object);
            return weak_version;
        }
    }
    std::weak_ptr<GameObject> empty_ptr{};
    return empty_ptr;
}

void State::StartArray(){
    for(auto& teste: objectArray){
        teste->Start();
    }
}

void State::UpdateArray(float dt){
    for(std::shared_ptr<GameObject> gameObject : objectArray){
        gameObject->Update(dt);
    }
}

void State::RenderArray(){
    for(std::shared_ptr<GameObject> gameObject: objectArray){
        gameObject->Render();
    }
}

bool State::PopRequested(){
    return popRequested;
}

bool State::QuitRequested(){
    return quitRequested;
}
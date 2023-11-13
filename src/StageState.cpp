#include "../Headers/StageState.h"
#include "../Headers/Game.h"
#include "../Headers/Camera.h"
#include "../Headers/Alien.h"
#include "../Headers/Sound.h"
#include "../Headers/TileMap.h"
#include "../Headers/InputManager.h"
#include "../Headers/CameraFollower.h"
#include <iostream>

StageState:: StageState() : State(){
	GameObject *object = new GameObject();
	Sprite *backGround = new Sprite("../DATA/img/ocean.jpg", *object);
	backgroundMusic  = new Music("../DATA/audio/stageState.ogg");
    object->AddComponent((std::shared_ptr<Sprite>)  backGround);

    CameraFollower *cameraFollower = new CameraFollower(*object);
    object->AddComponent((std::shared_ptr<CameraFollower>) cameraFollower);

    object->box.x = 0;
    object->box.y = 0;
    object->box.w = backGround->GetWidth();
    object->box.h = backGround->GetHeight();

    GameObject* map = new GameObject();
    map->box.x = 0;
    map->box.y = 0;
    TileSet* tileSet = new TileSet(64, 64, "../DATA/img/tileset.png");
    TileMap* tileMap = new TileMap(*map, "../DATA/Tiles/tileMap.txt", tileSet);
    map->AddComponent((std::shared_ptr<TileMap>) tileMap);
    map->box.x = 0;
    map->box.y = 0;

    GameObject* alienObject = new GameObject();
    alienObject->box.x = 512;
    alienObject->box.y = 300;
    Alien* alienComponent = new Alien(*alienObject, 0);
    alienObject->AddComponent(std::shared_ptr<Alien>(alienComponent));
    
    objectArray.emplace_back(object);
    objectArray.emplace_back(map);
    objectArray.emplace_back(alienObject);
    backgroundMusic->Play(-1);
}

StageState::~StageState(){
    objectArray.clear();
}

void StageState::Update(float dt) {
    Camera::Update(dt);

    if ((InputManager::GetInstance().KeyPress(ESCAPE_KEY)) || (InputManager::GetInstance().QuitRequested())){
        popRequested = true;
    }
    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
    for (int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        }
    }
}
void StageState::LoadAssets(){
}

void StageState::Render() {
    
    for (std::vector<int>::size_type i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

void StageState::Start(){
    LoadAssets();
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
}
void StageState::Pause(){
    backgroundMusic->Stop(0);
}

void StageState::Resume(){
    backgroundMusic->Play();
}
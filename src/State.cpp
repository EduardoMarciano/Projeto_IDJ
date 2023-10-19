#include "../Headers/Game.h"
#include "../Headers/Camera.h"
#include "../Headers/Alien.h"
#include "../Headers/Sound.h"
#include "../Headers/TileMap.h"
#include "../Headers/InputManager.h"
#include "../Headers/CameraFollower.h"

State:: State() : quitRequested(false), started(false){
	GameObject *object = new GameObject();
	Sprite *backGround = new Sprite("../DATA/img/ocean.jpg", *object);
	music  = new Music("../DATA/audio/stageState.ogg");
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
    music->Play(-1);
}

State::~State(){
    objectArray.clear();
}

void State::LoadAssets() {
}

void State::Update(float dt) {
    Camera::Update(dt);

    if ((InputManager::GetInstance().KeyPress(ESCAPE_KEY)) || (InputManager::GetInstance().QuitRequested())){
        quitRequested = true;
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

void State::Render() {
    
    for (std::vector<int>::size_type i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::Start(){
    LoadAssets();
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
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
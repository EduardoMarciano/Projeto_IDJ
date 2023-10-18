#include "../Headers/Game.h"
#include "../Headers/Camera.h"
#include "../Headers/Face.h"
#include "../Headers/TileMap.h"
#include "../Headers/InputManager.h"
#include "../Headers/CameraFollower.h"

State:: State() : quitRequested(false), started(false){
	GameObject *object = new GameObject();
	bg     = new Sprite("../DATA/img/ocean.jpg", *object);
	music  = new Music("../DATA/audio/stageState.ogg");
    object->AddComponent(bg);

    CameraFollower *cameraFollower = new CameraFollower(*object);
    object->AddComponent(cameraFollower);

    object->box.x = 0;
    object->box.y = 0;
    object->box.w = bg->GetWidth();
    object->box.h = bg->GetHeight();

    GameObject* map = new GameObject();
    map->box.x = 0;
    map->box.y = 0;
    TileSet* tileSet = new TileSet(64, 64, "../DATA/img/tileset.png");
    TileMap* tileMap = new TileMap(*map, "../DATA/Tiles/tileMap.txt", tileSet);
    map->AddComponent(tileMap);
    map->box.x = 0;
    map->box.y = 0;

    objectArray.emplace_back(object);
    objectArray.emplace_back(map);
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
    else if (InputManager::GetInstance().KeyPress(SPACEBAR_KEY)){
    
    Vec2 obj = Vec2(200, 0).GetRotated((-M_PI + M_PI * (rand() % 1001) / 500.0)) + Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
    AddObject((int)obj.x  - Camera::pos.x, (int)obj.y  - Camera::pos.y);
    
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

void State::AddObject(int mouseX, int mouseY) {
    GameObject *object = new GameObject();
	object->box.x = mouseX;
    object->box.y = mouseY;

    Sprite *sprite = new Sprite("../DATA/img/penguinface.png", *object);
	object->box.w = sprite->GetWidth();
    object->box.h = sprite->GetHeight();
    
	Sound *sound = new Sound(*object, "../DATA/audio/boom.wav");
	Face *face = new Face(*object);

	object->AddComponent(sprite);
    object->AddComponent(sound);
    object->AddComponent(face);
    objectArray.emplace_back(object);
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
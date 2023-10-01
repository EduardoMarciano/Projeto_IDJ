#include "../Headers/Game.h"
#include "../Headers/Sound.h"
#include "../Headers/Face.h"
#include "../Headers/TileMap.h"
#include "../Headers/InputManager.h"
#include <algorithm> 

State:: State() : quitRequested(false){
	GameObject *object = new GameObject();
	bg     = new Sprite("../DATA/img/ocean.jpg", *object);
	music  = new Music("../DATA/audio/stageState.ogg");
    object->AddComponent(bg);

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
    if ((InputManager::GetInstance().KeyPress(ESCAPE_KEY)) || (InputManager::GetInstance().QuitRequested())){
        quitRequested = true;
    }
    else if (InputManager::GetInstance().KeyPress(SPACEBAR_KEY)){
    
    Vec2 objPos = Vec2(200, 0).GetRotated((-M_PI + M_PI * (rand() % 1001) / 500.0)) + Vec2(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY());
    AddObject((int)objPos.x, (int)objPos.y);
    
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
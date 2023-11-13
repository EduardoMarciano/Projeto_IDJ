#include "../Headers/TitleState.h"
TitleState::TitleState(): State(){
    
    GameObject* titleObj = new GameObject();
    Sprite *titleImage= new Sprite("../DATA/img/title.jpg", *titleObj);
    titleObj->AddComponent((std::shared_ptr<Sprite>)  titleImage);

    objectArray.emplace_back(titleObj);   
}

TitleState::~TitleState(){
    objectArray.clear();
}

void TitleState::Update(float dt){
    if ((InputManager::GetInstance().KeyPress(ESCAPE_KEY)) || (InputManager::GetInstance().QuitRequested())){
        quitRequested = true;
    }
    else if(InputManager::GetInstance().KeyPress(SPACEBAR_KEY)){
        StageState* newState = new StageState();
        Game::GetInstance().Push(newState);
    }
}

void TitleState::LoadAssets(){}

void TitleState::Render() {
    
    for (std::vector<int>::size_type i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

void TitleState::Start(){
    LoadAssets();
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
}
void TitleState::Pause(){}

void TitleState::Resume(){}
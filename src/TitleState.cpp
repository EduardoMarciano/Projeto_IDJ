#include "../Headers/Camera.h"
#include "../Headers/TitleState.h"
#include <string>
TitleState::TitleState(): State(){
    
    GameObject* titleObj = new GameObject();
    Sprite *titleImage= new Sprite("../DATA/img/title.jpg", *titleObj);
    titleObj->AddComponent((std::shared_ptr<Sprite>)  titleImage);

    objectArray.emplace_back(titleObj);
    
    GameObject *textObj = new GameObject();
    std::string texto = "PRESS SPACEBAR TO PLAY";
    Text* startText = new Text(*textObj, "../DATA/Font/basicFont.ttf", 64, TextStyle::BLENDED,texto, {200, 200, 200});
    textObj->AddComponent((std::shared_ptr<Text>) startText);
    textObj->box.SetCenter(Vec2((float)(Game::GetInstance().GetWidth())/2, (float)(Game::GetInstance().GetHeight())/2));
    objectArray.emplace_back(textObj);
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
    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
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

void TitleState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;

}
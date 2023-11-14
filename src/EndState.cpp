#include "../Headers/Game.h"
#include "../Headers/Camera.h"
#include "../Headers/EndState.h"
#include "../Headers/GameData.h"
#include "../Headers/InputManager.h"

EndState::EndState() : State::State(){   
    backgroundMusic  = new Music();
    Sprite* endSprite;
    GameObject* endSpriteObj = new GameObject();


    Text* text;
    std::string message;
    GameObject* textObj = new GameObject();

    if (GameData::playerVictory){
        message = "YOU'VE WON";
        backgroundMusic->Open("../DATA/audio/endStateWin.ogg");
        endSprite = new Sprite("../DATA/img/win.jpg", *endSpriteObj);
    }
    else{
        message = "Oh no! You have lost!";
        backgroundMusic->Open("../DATA/audio/endStateLose.ogg");
        endSprite = new Sprite("../DATA/img/lose.jpg", *endSpriteObj);
    }
    text = new Text(*textObj, "../DATA/Font/basicFont.ttf", 64, TextStyle::BLENDED,message, {200, 200, 200});
    textObj->box.SetCenter(Vec2((float)(Game::GetInstance().GetWidth())/2, (float)(Game::GetInstance().GetHeight())/2));
    
    endSpriteObj->AddComponent((std::shared_ptr<Sprite>) endSprite);
    textObj ->AddComponent((std::shared_ptr<Text>) text);
        
    objectArray.emplace_back(endSpriteObj);
    objectArray.emplace_back(textObj);
    backgroundMusic->Play(-1);
}

EndState::~EndState(){
    backgroundMusic->Stop();
}

void EndState::LoadAssets(){
    
}

void EndState::Update(float dt){
    if (InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().KeyPress(SPACEBAR_KEY)){
        TitleState* title = new TitleState();
        Game::GetInstance().Push(title);
        popRequested = true;
    }
    for (int i = 0; i != (int)objectArray.size(); i++){
        objectArray[i]->Update(dt);
    }
}

void EndState::Render() {
    
    for (std::vector<int>::size_type i = 0; i < objectArray.size(); i++){
        objectArray[i]->Render();
    }
}

void EndState::Start(){
    LoadAssets();
    for (int i = 0; i < (int)objectArray.size(); i++){
        objectArray[i]->Start();
    }
    started = true;
}
void EndState::Pause(){
    backgroundMusic->Stop(0);
}

void EndState::Resume(){
    Camera::pos.x = 0;
    Camera::pos.y = 0;
    backgroundMusic->Play(-1);
}
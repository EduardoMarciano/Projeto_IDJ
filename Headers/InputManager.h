#ifndef InputManager_H
#define InputManager_H

#define KEY_F  'f'
#define KEY_G  'g'

#define UP_ARROW_KEY        SDLK_UP
#define LEFT_ARROW_KEY      SDLK_LEFT
#define DOWN_ARROW_KEY      SDLK_DOWN
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define ESCAPE_KEY          SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT
#define SPACEBAR_KEY 32

#include <unordered_map>

class InputManager{ 
    public:
        InputManager();
        ~InputManager ();
        static InputManager& GetInstance ();

        void Update();
        
        int GetMouseX ();
        int GetMouseY();

        bool KeyPress  (int key);
        bool KeyRelease (int key);
        bool IsKeyDown (int key);

        bool MousePress     (int button);
        bool MouseRelease   (int button);
        bool IsMouseDown    (int button);

        bool QuitRequested ();
        
    private:
        int mouseX;
        int mouseY;
        int updateCounter;
        int  mouseUpdate[6];
        
        bool mouseState[6];
        bool quitRequested;

        std::unordered_map<int, bool> keyState;
        std::unordered_map<int, int> keyUpdate;

};
#endif
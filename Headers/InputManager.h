#ifndef InputManager_H
#define InputManager_H

class InputManager{ 
    public:
        InputManager();
        ~InputManager ();
        InputManager& GetInstance ();

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

};
#endif
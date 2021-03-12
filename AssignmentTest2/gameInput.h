#pragma once
#include <dinput.h>
#include "systemClass.h"

class GameInput
{

private:
    static GameInput* instance;
    LPDIRECTINPUT8 dInput;
    LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
    LPDIRECTINPUTDEVICE8  dInputMouseDevice;
    BYTE  diKeys[256];
    DIMOUSESTATE mouseState;
    int previousMouseState[3];
    int previousKeyState[256];

    GameInput();
    bool ReadKeyboard();
    bool ReadMouse();

public:
    struct mousePosition {
        int x;
        int y;
    } mousePosition;
    static GameInput* getInstance();
    bool createInput();
    void update();
    void release();

    bool EscapeKeyPressed();
    bool MouseButtonPressed(int button);
    bool MouseButtonClick(int button);
    bool KeyboardKeyPressed(int code);
    bool KeyboardKeyHold(int code);
};
#include "gameInput.h"
#include "systemClass.h"

GameInput* GameInput::instance = 0;

GameInput::GameInput()
{
    HRESULT result;
    DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

    result = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboard, NULL);

    dInputKeyboard->SetDataFormat(&c_dfDIKeyboard);
    dInputKeyboard->SetCooperativeLevel(GameWin::getInstance()->g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    dInputKeyboard->Acquire();

    result = dInput->CreateDevice(GUID_SysMouse, &dInputMouse, NULL);

    dInputMouse->SetDataFormat(&c_dfDIMouse);
    dInputMouse->SetCooperativeLevel(GameWin::getInstance()->g_hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
    dInputMouse->Acquire();

    mousePosition.x = 0;
    mousePosition.y = 0;

    ZeroMemory(diKeys, sizeof(diKeys));
    ZeroMemory(&mouseState, sizeof(mouseState));
}

bool GameInput::ReadKeyboard()
{
    HRESULT result;
    // Read the keyboard device.
    result = dInputKeyboard->GetDeviceState(sizeof(diKeys), (LPVOID)diKeys);
    if (FAILED(result))
    {
        // If the keyboard lost focus or was not acquired then try to get control back.
        if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
        {
            dInputKeyboard->Acquire();
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool GameInput::ReadMouse()
{
    HRESULT result;

    result = dInputMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);
    if (FAILED(result))
    {
        if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
        {
            dInputMouse->Acquire();
        }
        else
        {
            return false;
        }
    }

    return true;
}
void GameInput::update()
{
    GameInput::ReadKeyboard();
    GameInput::ReadMouse();
    mousePosition.x += mouseState.lX;
    mousePosition.x = max(mousePosition.x, 0);
    mousePosition.x = min(mousePosition.x, 1080); // screen sizes

    mousePosition.y += mouseState.lY;
    mousePosition.y = max(mousePosition.y, 0);
    mousePosition.y = min(mousePosition.y, 720);

}

GameInput* GameInput::getInstance()
{
    if (!instance)
    {
        instance = new GameInput;
    }

    return instance;
}

bool GameInput::createInput()
{
    HRESULT result;
    DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

    LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
    result = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);

    if (FAILED(result))
    {
        return false;
    }
    dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
    dInputKeyboardDevice->SetCooperativeLevel(GameWin::getInstance()->g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    dInputKeyboardDevice->Acquire();

    LPDIRECTINPUTDEVICE8  dInputMouseDevice;
    result = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);

    if (FAILED(result))
    {
        return false;
    }
    dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
    dInputMouseDevice->SetCooperativeLevel(GameWin::getInstance()->g_hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
    dInputMouseDevice->Acquire();

    return true;
}
void GameInput::release()
{
    dInputKeyboard->Unacquire();
    dInputKeyboard->Release();
    dInputKeyboard = NULL;

    dInputMouse->Unacquire();
    dInputMouse->Release();
    dInputMouse = NULL;

    dInput->Release();
    dInput = NULL;
}

bool GameInput::EscapeKeyPressed()
{
    if (diKeys[DIK_ESCAPE] & 0x80)
    {
        return true;
    }

    return false;
}

bool GameInput::MouseButtonPressed(int button)
{
    if (mouseState.rgbButtons[button] & 0x80)
    {
        return true;
    }

    return false;
}

bool GameInput::MouseButtonClick(int button)
{
    if (mouseState.rgbButtons[button] & 0x80)
    {
        previousMouseState[button] = 1;
    }
    else if (previousMouseState[button] == 1)
    {
        previousMouseState[button] = 0;
        return true;
    }

    return false;
}

bool GameInput::KeyboardKeyHold(int code)
{
    if (diKeys[code] & 0x80)
    {
        return true;
    }

    return false;
}

bool GameInput::KeyboardKeyPressed(int code)
{
    if (diKeys[code] & 0x80)
    {
        previousKeyState[code] = 1;
    }
    else if (previousKeyState[code] == 1)
    {
        previousKeyState[code] = 0;
        return true;
    }
    return false;
}
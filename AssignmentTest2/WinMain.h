#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class GameWin
{
private:

public:
	GameWin();
	static GameWin* instance;
	HWND g_hWnd = NULL;
	WNDCLASS wndClass;
	HINSTANCE hInstance;
	static GameWin* getInstance();
	void createGameWindow();
	void clearGameWindow();
	bool loopGameWindow();

};

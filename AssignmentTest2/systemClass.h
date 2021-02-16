#pragma once
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_
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
	bool createGameWindow();
	void clearGameWindow();
	bool loopGameWindow();

};

#endif

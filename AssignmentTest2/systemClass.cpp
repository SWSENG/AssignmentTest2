#include "systemClass.h"
#include"resource.h"
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

LRESULT	 CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

GameWin* GameWin::instance = 0;

GameWin* GameWin::getInstance()
{
	if (!instance)
	{
		instance = new GameWin;
	}

	return instance;
}

GameWin::GameWin()
{
	g_hWnd = NULL;
	hInstance = GetModuleHandle(NULL);
}

bool GameWin::createGameWindow()
{
	ZeroMemory(&wndClass, sizeof(wndClass));

	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(IDC_CURSOR2));
	wndClass.hInstance = hInstance;	//	GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	//wndClass.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	RegisterClass(&wndClass);

	//Create the Window.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Move", WS_OVERLAPPEDWINDOW, 0, 100, SCREEN_WIDTH, SCREEN_HEIGHT, NULL, NULL, hInstance, NULL);
	ShowWindow(g_hWnd, 1);
	ShowCursor(true);

	return true;
}

void GameWin::clearGameWindow()
{
	//	Free up the memory.
	UnregisterClass(wndClass.lpszClassName, hInstance);
}

bool GameWin::loopGameWindow()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT);
		//	Translate the message 
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);
	}


	return msg.message != WM_QUIT;
}

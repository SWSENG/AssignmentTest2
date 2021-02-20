#include"systemClass.h"
#include"gameGraphic.h";
#include<stdio.h>
#include <d3d9.h>
#include"gameEngine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameWin* gWin = gWin->getInstance();
	Game* game = new Game();

	if (gWin->createGameWindow())
	{
		MSG msg;
		game = new Game();

		if (game->Initialize(gWin->g_hWnd, 1280, 720))
		{
			while (true)
			{
				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				if (msg.message == WM_QUIT) break;
				else
				{
					game->Run();
				}
			}

			delete game;
			return msg.wParam;
		}

		return 0;
	}
}
#include"systemClass.h"
#include"gameGraphic.h";
#include<stdio.h>
#include <d3d9.h>

//--------------------------------------------------------------------
//
int main()//WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameWin* gWin = new GameWin();
	gWin->createGameWindow();
	GraphicsDevice* gDevice = new GraphicsDevice();
	gDevice->Initialize(gWin->g_hWnd, true);

	while (gWin->loopGameWindow())
	{
		//	To Do:
		//	Update.

		//	Clear the back buffer.
		gDevice->Clear(D3DCOLOR_XRGB(0, 100, 100));

		//	Begin the scene
		gDevice->Begin();

		//	To Do:
		//	Drawing.

		//	End the scene
		gDevice->End();

		//	Present the back buffer to screen
		gDevice->Present();
	}

	//	Release the device when exiting.
	gDevice->~GraphicsDevice();
	//	Reset pointer to NULL, a good practice.
	gDevice = NULL;

	gWin->clearGameWindow();

	delete gDevice;
	gDevice = nullptr;
	delete gWin;
	gWin = nullptr;

	return 0;
}
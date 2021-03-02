#include"systemClass.h"
#include"gameGraphic.h"
#include"gameInput.h"
#include"gameStateManager.h"

int main()//WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameWin* gWin = GameWin::getInstance();
	gWin->createGameWindow();
	GameGraphic* gGraphic = GameGraphic::getInstance();
	gGraphic->Initialize(gWin->g_hWnd, true);
	GameInput* gInput = GameInput::getInstance();
	gInput->createInput();
	gameStateManager* gameStateManager = gameStateManager::getInstance();
	
	while (gWin->loopGameWindow())
	{
		gInput->update();
		gGraphic->Clear(0);
		gGraphic->Begin();
		gameStateManager->Update();
		gameStateManager->Draw();
		gGraphic->End();
		gGraphic->Present();
	}

	gameStateManager->releaseInstance();
	gInput->release();
	gGraphic->~GameGraphic();
	gWin->clearGameWindow();

	return 0;
}
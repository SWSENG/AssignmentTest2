#include "gameGraphic.h"

GameGraphic* GameGraphic::instance = 0;

GameGraphic::GameGraphic()
{
	//Constructor
}

bool GameGraphic::Initialize(HWND hWnd, bool windowed)
{
	//Create Direct 3D Pointer
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dPP;
	ZeroMemory(&d3dPP, sizeof(d3dPP));
	d3dPP.Windowed = windowed; //Boolean determines if we are running in Windowed mode.
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD; //fastest
	d3dPP.hDeviceWindow = hWnd; //use the window we set up
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = 1200;
	d3dPP.BackBufferHeight = 1200;

	//create the device
	if (!SUCCEEDED(direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &d3dPP, &device)))
	{
		return false;
	}

	return true;
}

GameGraphic* GameGraphic::getInstance()
{
	if (!instance)
	{
		instance = new GameGraphic;
	}

	return instance;
}

void GameGraphic::Clear(D3DCOLOR color)
{
	//2nd param 'NULL' clears the entire back buffer.
	device->Clear(0, NULL, D3DCLEAR_TARGET, (0, 255, 0), 1.0f, 0);
}

void GameGraphic::Begin()
{
	device->BeginScene();
}

void GameGraphic::End()
{
	device->EndScene();
}

void GameGraphic::Present()
{
	//Present our scene to the window.
	device->Present(NULL, NULL, NULL, NULL);
}

GameGraphic::~GameGraphic()
{
	if (device)
	{
		device->Release();
		device = 0;
	}

	if (direct3d)
	{
		direct3d->Release();
		direct3d = 0;
	}
}

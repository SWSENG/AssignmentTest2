#include "gameGraphic.h"


GraphicsDevice::GraphicsDevice()
{
	//Constructor
}

bool GraphicsDevice::Initialize(HWND hWnd, bool windowed)
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
	d3dPP.BackBufferWidth = 1280;
	d3dPP.BackBufferHeight = 720;

	//create the device
	if (!SUCCEEDED(direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &d3dPP,&device)))
	{
		return false;
	}

	return true;
}

void GraphicsDevice::Clear(D3DCOLOR color)
{
	//2nd param 'NULL' clears the entire back buffer.
	device->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0);
}

void GraphicsDevice::Begin()
{
	device->BeginScene();
}

void GraphicsDevice::End()
{
	device->EndScene();
}

void GraphicsDevice::Present()
{
	//Present our scene to the window.
	device->Present(NULL, NULL, NULL, NULL);
}

GraphicsDevice::~GraphicsDevice()
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

#pragma once
#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#include <d3d9.h>
#include <d3dx9.h>

class GameGraphic
{
public:
	GameGraphic();
	~GameGraphic();
	static GameGraphic* getInstance();
	bool Initialize(HWND hWnd, bool windowed);
	void Clear(D3DCOLOR color);
	void Begin();
	void End();
	void Present();

	//Public Pointers
	LPDIRECT3DDEVICE9 device;
private:
	//Private Pointers
	LPDIRECT3D9 direct3d;
	static GameGraphic* instance;
};

#endif
#pragma once
#include"gameState.h"
#include"gameGraphic.h"

class gameMenu :public gameState
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	LPD3DXSPRITE sprite1;
	LPDIRECT3DTEXTURE9 texture1;
	LPD3DXFONT font;
	RECT textRect;
	D3DXVECTOR2 fontPosition;
	D3DXMATRIX mat;
public:
	gameMenu();
	~gameMenu();

	void init();
	void Update();
	void fixedUpdate();
	void Draw();
	void Release();
};


#pragma once
#include"gameState.h"
#include"gameGraphic.h"

class tutorial :public gameState
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DTEXTURE9 texture1;
	LPD3DXSPRITE sprite;
	LPD3DXSPRITE sprite1;
	LPD3DXFONT font;
	RECT textRect;
	D3DXVECTOR2 fontPosition;
	D3DXMATRIX mat;
public:
	tutorial();
	~tutorial();

	void init();
	void Update();
	void fixedUpdate();
	void Draw();
	void Release();
};


#pragma once
#include"gameState.h"
#include"gameGraphic.h"


class gameLevel :public gameState
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	LPD3DXFONT font;
	LPD3DXLINE line;
	RECT spriteRect;
	RECT textRect;
	D3DXMATRIX mat;
	float rotation;
	int x = 0;
	int hp = 0;
	D3DXVECTOR2 spriteCentre;
	D3DXVECTOR2 trans;
	D3DXVECTOR2 scaling;
public:
	gameLevel();
	~gameLevel();

	void init();
	void Update();
	void Draw();
	void Release();
};


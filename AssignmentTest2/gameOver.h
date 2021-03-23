#pragma once
#include"gameState.h"
#include"gameGraphic.h"

class gameOver :public gameState
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	LPD3DXSPRITE fontSprite;
	LPD3DXFONT font;
	RECT textRect;
	D3DXVECTOR2 fontPosition;
	D3DXMATRIX mat;
	D3DXMATRIX mat1;
	D3DXVECTOR2 gameOverPosition;
	LPD3DXFONT scoreFont;

public:
	gameOver();
	~gameOver();

	void init();
	void Update();
	void fixedUpdate();
	void Draw();
	void Release();

};


#pragma once
#include"gameState.h"
#include"gameGraphic.h"
#include"gameSound.h"

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

	gameSound* sound;
public:
	gameMenu();
	~gameMenu();

	bool playMusic;
	void init();
	void Update();
	void fixedUpdate();
	void Draw();
	void Release();
};


#pragma once
#include"gameState.h"
#include"gameGraphic.h"

class gameMenu :public gameState
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
public:
	gameMenu();
	~gameMenu();

	void init();
	void Update();
	void fixedUpdate();
	void Draw();
	void Release();
};


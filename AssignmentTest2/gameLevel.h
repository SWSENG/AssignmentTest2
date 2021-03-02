#pragma once
#include"gameState.h"
#include"gameGraphic.h"


class gameLevel :public gameState
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	RECT spriteRect;
	D3DXMATRIX mat;
	float rotation = 0;
	int x = 0;
	float directionX = 1;
	D3DXVECTOR2 spriteCentre;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scaling;

	D3DXVECTOR2 characterSize;
	int characterCurrentFrame;
	float animationDuration;
	float animationTimer;
	int animationRow;
	bool isCharacterMoving;
	float speed;
	D3DXVECTOR2 direction;

public:
	gameLevel();
	~gameLevel();

	void init();
	void Update();
	void fixedUpdate();
	void Draw();
	void Release();
};


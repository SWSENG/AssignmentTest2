#pragma once
#include"gameGraphic.h"

class player
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	D3DXMATRIX mat;
	float rotation = 0;
	int x = 0;
	float directionX = 1;
	D3DXVECTOR2 spriteCentre;
	D3DXVECTOR2 characterSize;
	D3DXVECTOR2 scaling;

	int characterCurrentFrame;
	float animationDuration;
	float animationTimer;
	int animationRow;
	

public:
	player();
	~player();
	RECT playerRect;
	D3DXVECTOR2 playerPosition;
	D3DXVECTOR2 playerDirection;
	D3DXVECTOR3 playerCenter;
	RECT spriteSize;

	bool isCharacterMoving;
	float playerSpeed;

	void init();
	void Update();
	void fixedUpdate();
	void Draw();
	void Release();
};


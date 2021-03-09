#pragma once
#include"gameGraphic.h"

class enemy
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

	D3DXVECTOR2 enemySize;
	int enemyCurrentFrame;
	float enemyDuration;
	float enemyTimer;
	int enemyRow;
	bool isEnemyMoving;
	float enemySpeed;
	D3DXVECTOR2 direction;

public:
	enemy();
	~enemy();

	void init();
	void Update();
	void fixedUpdate();
	void Draw();
	void Release();
};


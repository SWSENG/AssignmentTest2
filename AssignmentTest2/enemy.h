#pragma once
#include"gameGraphic.h"
#include"collision.h"

class enemy :public collision
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	D3DXMATRIX mat;
	float rotation = 0;
	int x = 0;
	float directionX = 1;
	D3DXVECTOR2 spriteCentre;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 enemySize;
	int enemyCurrentFrame;
	float enemyDuration;
	float enemyTimer;
	int enemyRow;
	float enemySpeed;
	D3DXVECTOR2 direction[8];

public:
	enemy();
	~enemy();

	RECT sampleEnemyRect;
	RECT enemyRect[4];
	D3DXVECTOR2 enemyPosition[8];
	bool isEnemyMoving;

	void init();
	void Update();
	void fixedUpdate();
	void Draw();
	void Release();

	bool checkCollision(D3DXVECTOR2 pos1, RECT rect1, D3DXVECTOR2 pos2, RECT rect2);
	int checkSideOfCollision(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2);
};


#pragma once
#include"gameGraphic.h"
#include"collision.h"
#include"particle.h"
#include<vector>

class enemy :public collision
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	D3DXMATRIX mat;
	int x = 0;
	D3DXVECTOR2 spriteCentre;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 enemySize;
	int enemyCurrentFrame;
	float enemyDuration;
	float enemyTimer;
	int enemyRow[5];

	float currentBouncingLeft;
	float currentBouncingRight;
	float currentBouncingTop;
	float currentBouncingBottom;

	float nextBouncingLeft;
	float nextBouncingRight;
	float nextBouncingTop;
	float nextBouncingBottom;

	LPDIRECT3DTEXTURE9 particle_texture;
	std::vector<particle*> particleList;
public:
	enemy();
	~enemy();

	RECT sampleEnemyRect;
	RECT enemyRect[5];
	D3DXVECTOR2 enemyPosition[5];
	bool isEnemyMoving;
	D3DXVECTOR2 direction[5];
	float enemySpeed;

	void init();
	void Update();
	void fixedUpdate();
	void Draw();
	void Release();

	bool checkCollision(D3DXVECTOR2 pos1, RECT rect1, D3DXVECTOR2 pos2, RECT rect2);
	int checkSideOfCollision(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2);

	void startParticle(D3DXVECTOR2 position);
};


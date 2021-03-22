#pragma once
#include"gameState.h"
#include"gameGraphic.h"
#include"gameBackground.h"
#include"enemy.h"
#include"player.h"
#include"heart.h"
#include"flag.h"
//#include"collision.h"
#include"font.h"

class gameLevel :public gameState
{
private:
	GameBackround* background;
	enemy* drawEnemy;
	player* drawPlayer;
	heart* drawHeart;
	flag* drawFlag;
	collision* collisionObject;
	font* drawFont;

	LPD3DXLINE line;
	D3DXVECTOR2 playerVertices[5];
	D3DXVECTOR2 enemyVertices[5];

	LPD3DXFONT scoreFont;
	LPD3DXFONT hpFont;
	LPD3DXSPRITE sprite;
	LPD3DXSPRITE sprite1;
	RECT textRect;
	RECT textRect2;
	D3DXVECTOR2 font1Position;
	D3DXVECTOR2 font2Position;
	D3DXMATRIX mat;
	D3DXMATRIX mat1;
	int hp;
public:
	int score;

	gameLevel();
	~gameLevel();
	bool checkCollision(D3DXVECTOR2 pos1, RECT rect1, D3DXVECTOR2 pos2, RECT rect2);
	int checkSideOfCollision(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2);
	void init();
	void Update();
	void fixedUpdate();
	void Draw();
	void Release();
};
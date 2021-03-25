#pragma once
#include"gameState.h"
#include"gameGraphic.h"
#include"gameBackground.h"
#include"enemy.h"
#include"player.h"
#include"heart.h"
#include"flag.h"
#include"font.h"
#include"gameSound.h"

class gameLevel :public gameState
{
private:
	static gameLevel* instance;
	GameBackround* background;
	enemy* drawEnemy;
	player* drawPlayer;
	heart* drawHeart;
	flag* drawFlag;
	collision* collisionObject;
	font* drawFont;
	gameSound* sound;
	gameSound* hitByEnemysound;

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
	int score;
public:
	gameLevel();
	~gameLevel();
	static gameLevel* getInstance();
	bool checkCollision(D3DXVECTOR2 pos1, RECT rect1, D3DXVECTOR2 pos2, RECT rect2);
	int checkSideOfCollision(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2);
	int getScore();
	void setScore(int score);
	int getHp();
	void setHp(int hp);

	void init();
	void Update();
	void fixedUpdate();
	void Draw();
	void Release();
	void releaseInstance();
};
#pragma once
#include"gameState.h"
#include"gameGraphic.h"
#include"gameBackground.h"
#include"enemy.h"
#include"player.h"

class gameLevel :public gameState
{
private:
	GameBackround* background;
	enemy* drawEnemy;
	player* drawPlayer;

public:
	gameLevel();
	~gameLevel();

	void init();
	void Update();
	void fixedUpdate();
	void Draw();
	void Release();
};


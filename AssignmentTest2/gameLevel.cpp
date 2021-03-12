#include "gameLevel.h"
#include"gameInput.h"
#include<string>
#include<iostream>
#include"gameStateManager.h"

using namespace std;

gameLevel::gameLevel()
{

}

gameLevel::~gameLevel()
{
}

void gameLevel::init()
{
	background = new GameBackround();
	background->Initialize(GameGraphic::getInstance()->device, "img/background.png", 1200, 1700);
	drawPlayer = new player();
	drawPlayer->init();
	drawEnemy = new enemy;
	drawEnemy->init();
	drawHeart = new heart();
	drawHeart->init();
	drawFlag = new flag();
	drawFlag->init();
}

void gameLevel::Update()
{
	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_ESCAPE))
	{
	PostQuitMessage(0);
	}
	drawPlayer->Update();
	drawEnemy->Update();
	drawFlag->Update();
}

void gameLevel::fixedUpdate()
{
	drawPlayer->fixedUpdate();
	drawEnemy->fixedUpdate();
	drawFlag->fixedUpdate();
}

void gameLevel::Draw()
{
	background->Draw();
	drawPlayer->Draw();
	drawEnemy->Draw();
	drawHeart->Draw();
	drawFlag->Draw();
}

void gameLevel::Release()
{
	background->~GameBackround();
	if (background) { delete background; background = nullptr; }
	drawPlayer->Release();
	if (drawPlayer) { delete drawPlayer; drawPlayer = nullptr; }
	drawEnemy->Release();
	if (drawEnemy) { delete drawEnemy; drawEnemy = nullptr; }
	drawHeart->Release();
	if (drawHeart) { delete drawHeart; drawHeart = nullptr; }
	drawFlag->Release();
	if (drawFlag) { delete drawFlag; drawFlag = nullptr; }
}
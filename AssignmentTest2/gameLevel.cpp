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
}

void gameLevel::Update()
{
	drawPlayer->Update();
	//if (GameInput::getInstance()->KeyboardKeyPressed(DIK_L))
	//{
	//	gameStateManager::getInstance()->changeGameState(0);
	//}
}

void gameLevel::fixedUpdate()
{
	drawPlayer->fixedUpdate();
	drawEnemy->fixedUpdate();
}

void gameLevel::Draw()
{
	background->Draw();
	drawPlayer->Draw();
	drawEnemy->Draw();
}

void gameLevel::Release()
{
	background->~GameBackround();
	if (background) { delete background; background = nullptr; }
	drawPlayer->Release();
	if (drawPlayer) { delete drawPlayer; drawPlayer = nullptr; }
	drawEnemy->Release();
	if (drawEnemy) { delete drawEnemy; drawEnemy = nullptr; }
}
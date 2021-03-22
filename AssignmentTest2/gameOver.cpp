#include "gameOver.h"
#include"gameStateManager.h"
#include"gameInput.h"
#include"gameGraphic.h"
#include<string>
#include<iostream>

using namespace std;

gameOver::gameOver()
{
	font = NULL;
	texture = NULL;
	sprite = NULL;

	gameOverPosition.x = 450;
	gameOverPosition.y = 300;
	fontPosition.x = 450;
	fontPosition.y = 500;

	getScore = new (gameLevel);
}

gameOver::~gameOver()
{
}

void gameOver::init()
{
	D3DXCreateSprite(GameGraphic::getInstance()->device, &sprite);
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->device, "img/gameOver.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);
	D3DXCreateSprite(GameGraphic::getInstance()->device, &sprite);
	D3DXCreateFont(GameGraphic::getInstance()->device, 50, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &scoreFont);
}

void gameOver::Update()
{
	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_ESCAPE))
	{
		PostQuitMessage(0);
	}
	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_RETURN))
	{
		gameStateManager::getInstance()->changeGameState(0);
	}
}

void gameOver::fixedUpdate()
{
}

void gameOver::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, &gameOverPosition);
	sprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->SetTransform(&mat1);
	string str = to_string(getScore->score);
	D3DXMatrixTransformation2D(&mat1, NULL, 0.0, NULL, NULL, NULL, &fontPosition);
	scoreFont->DrawText(sprite, str.c_str(), -1, &textRect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void gameOver::Release()
{
	delete getScore;
	getScore = NULL;
	scoreFont->Release();
	scoreFont = NULL;
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
}

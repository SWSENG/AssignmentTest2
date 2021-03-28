#include "gameOver.h"
#include"gameStateManager.h"
#include"gameInput.h"
#include"gameGraphic.h"
#include<string>
#include<iostream>
#include"gameLevel.h"

using namespace std;

gameOver::gameOver()
{
	font = NULL;
	texture = NULL;
	sprite = NULL;
	fontSprite = NULL;

	gameOverPosition.x = 450;
	gameOverPosition.y = 300;
	fontPosition.x = 570;
	fontPosition.y = 500;

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
	D3DXCreateSprite(GameGraphic::getInstance()->device, &fontSprite);
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
		gameLevel::getInstance()->setScore(0);
		gameLevel::getInstance()->setHp(20);
		gameStateManager::getInstance()->changeGameState(0);
	}

}

void gameOver::fixedUpdate()
{
}

void gameOver::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, &gameOverPosition);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();

	fontSprite->Begin(D3DXSPRITE_ALPHABLEND);
	string str = to_string(gameLevel::getInstance()->getScore());
	D3DXMatrixTransformation2D(&mat1, NULL, 0.0, NULL, NULL, NULL, &fontPosition);
	fontSprite->SetTransform(&mat1);
	scoreFont->DrawText(fontSprite, str.c_str(), -1, &textRect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	fontSprite->End();
}

void gameOver::Release()
{
	fontSprite->Release();
	fontSprite = NULL;
	scoreFont = NULL;
	scoreFont->Release();
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
}

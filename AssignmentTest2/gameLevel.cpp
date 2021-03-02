#include "gameLevel.h"
#include"gameInput.h"
#include<string>
#include<iostream>
#include"gameStateManager.h"

using namespace std;

gameLevel::gameLevel()
{
	sprite = NULL;
	texture = NULL;
}

gameLevel::~gameLevel()
{
}

void gameLevel::init()
{

	D3DXCreateSprite(GameGraphic::getInstance()->device, &sprite);
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->device, "PlayerPaper.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);
	D3DXCreateFont(GameGraphic::getInstance()->device, 25, 0, 0, 1, false, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);
	D3DXCreateLine(GameGraphic::getInstance()->device, &line);

}

void gameLevel::Update()
{
	if (GameInput::getInstance()->MouseButtonClick(DIK_ESCAPE))
	{
		gameStateManager::getInstance()->changeGameState(gameStateManager::LEVEL);
	}

	spriteCentre = D3DXVECTOR2(0, 0);
	trans = D3DXVECTOR2(GameInput::getInstance()->mousePosition.x, GameInput::getInstance()->mousePosition.y);
	scaling = D3DXVECTOR2(1.0f, 1.0f);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &trans);

}

void gameLevel::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, NULL, NULL, &D3DXVECTOR3(95 - 24, 415 - 334, 0), D3DCOLOR_XRGB(255, 255, 255));
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &trans);
	string str = to_string(hp) + "%";
	font->DrawText(sprite, str.c_str(), -1, &textRect, DT_NOCLIP | DT_CENTER, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();

	D3DXVECTOR2 lineVertices[] = { D3DXVECTOR2(0,0),D3DXVECTOR2(GameInput::getInstance()->mousePosition.x, GameInput::getInstance()->mousePosition.y) };
	line->Begin();
	line->Draw(lineVertices, 2, D3DCOLOR_XRGB(0, 0, 0));
	line->End();
}

void gameLevel::Release()
{
	line->Release();
	line = NULL;
	font->Release();
	font = NULL;
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
}
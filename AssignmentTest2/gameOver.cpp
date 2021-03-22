#include "gameOver.h"
#include"gameStateManager.h"
#include"gameInput.h"
#include"gameGraphic.h"

gameOver::gameOver()
{
	font = NULL;
	texture = NULL;
	sprite = NULL;
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
}

void gameOver::Update()
{
	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_ESCAPE))
	{
		PostQuitMessage(0);
	}
	//if (GameInput::getInstance()->KeyboardKeyPressed(DIK_RETURN))
	//{
	//	gameStateManager::getInstance()->changeGameState(0);
	//}
}

void gameOver::fixedUpdate()
{
}

void gameOver::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void gameOver::Release()
{
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
}

#include "menu.h"
#include"gameStateManager.h"
#include"gameInput.h"
#include"gameGraphic.h"

gameMenu::gameMenu()
{
}

gameMenu::~gameMenu()
{
}

void gameMenu::init()
{
	D3DXCreateSprite(GameGraphic::getInstance()->device, &sprite);
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->device, "img/menu.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);
}

void gameMenu::Update()
{
	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_RETURN))
	{
		gameStateManager::getInstance()->changeGameState(1);
	}
}

void gameMenu::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void gameMenu::fixedUpdate()
{

}

void gameMenu::Release()
{
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
}

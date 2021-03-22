#include "tutorial.h"
#include"gameStateManager.h"
#include"gameInput.h"
#include"gameGraphic.h"

tutorial::tutorial()
{
	font = NULL;
	texture = NULL;
	texture1 = NULL;
	sprite = NULL;
	sprite1 = NULL;

	RECT textRect;
	textRect.left = 100;
	textRect.top = 100;
	textRect.right = 150;
	textRect.bottom = 125;

	fontPosition.x = 800;
	fontPosition.y = 800;
}

tutorial::~tutorial()
{
}

void tutorial::init()
{
	D3DXCreateSprite(GameGraphic::getInstance()->device, &sprite);
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->device, "img/menu.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->device, "img/tutorial.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture1);
	D3DXCreateSprite(GameGraphic::getInstance()->device, &sprite1);
	D3DXCreateFont(GameGraphic::getInstance()->device, 50, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);
}

void tutorial::Update()
{
	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_RETURN))
	{
		gameStateManager::getInstance()->changeGameState(2);
	}
}

void tutorial::fixedUpdate()
{
}

void tutorial::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(200, 200, 200));
	sprite->Draw(texture1, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
	sprite1->Begin(D3DXSPRITE_ALPHABLEND);
	sprite1->SetTransform(&mat);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, &fontPosition);
	font->DrawText(sprite1, "[PRESS ENTER TO SKIP]", -1, &textRect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	sprite1->End();
}

void tutorial::Release()
{
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
	texture1->Release();
	texture1 = NULL;
	sprite1->Release();
	sprite1 = NULL;
	font->Release();
	font = NULL;
}

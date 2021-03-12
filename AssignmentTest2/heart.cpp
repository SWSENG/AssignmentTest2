#include "heart.h"

heart::heart()
{
}

heart::~heart()
{
}

void heart::init()
{
	D3DXCreateSprite(GameGraphic::getInstance()->device, &sprite);
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->device, "img/heart.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);

	//Player init
	heartSize.x = 180;
	heartSize.y = 220;
	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.right = spriteRect.left + heartSize.x;
	spriteRect.bottom = spriteRect.top + heartSize.y;
	scaling.x = 0.5f;
	scaling.y = 0.5f;
	position.x = 0;
	position.y = 0;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &position);
}

void heart::Update()
{
}

void heart::fixedUpdate()
{
}

void heart::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void heart::Release()
{
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
}

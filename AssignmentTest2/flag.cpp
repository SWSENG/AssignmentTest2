#include "flag.h"

flag::flag()
{
	sprite = NULL;
	texture = NULL;
	flagSize.x = 64;
	flagSize.y = 80;
	flagCurrentFrame = 0;
	flagRect.top = 0;
	flagRect.left = 0;
	flagRect.right = flagRect.left + flagSize.x;
	flagRect.bottom = flagRect.top + flagSize.y;
	scaling.x = 1.0f;
	scaling.y = 1.0f;
	flagTimer = 0;
	flagDuration = 1.0f / 6;
	flagSpeed = (1.0f / flagDuration) * 60;
	flagRow = 0;
	direction.x = 0;
	direction.y = 0;

	flagPosition.x = 1 + (rand() % 1080);
	flagPosition.y = 1 + (rand() % 1080);
}

flag::~flag()
{
}

void flag::init()
{
	D3DXCreateSprite(GameGraphic::getInstance()->device, &sprite);
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->device, "img/flag.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);

}

void flag::Update()
{
	//position.x = 1 + (rand() % 1000);
	//position.y = 1 + (rand() % 1000);
}

void flag::fixedUpdate()
{
	flagTimer += 1 / 60.0f;
	D3DXVECTOR2 velocity = direction * (flagSpeed / 60.0f);
	flagPosition += velocity;
	if (flagTimer >= flagDuration)
	{
		flagTimer -= flagDuration;
		flagCurrentFrame++;
		flagCurrentFrame %= 2;
	}
	flagRect.top = flagRow * flagSize.y;
	flagRect.left = flagSize.x * flagCurrentFrame;
	flagRect.right = flagRect.left + flagSize.x;
	flagRect.bottom = flagRect.top + flagSize.y;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &flagPosition);

}

void flag::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &flagRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void flag::Release()
{
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
}

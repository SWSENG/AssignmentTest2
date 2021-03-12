#include "flag.h"

flag::flag()
{
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

	//Player init
	flagSize.x = 256;
	flagSize.y = 362;
	flagCurrentFrame = 0;
	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.right = spriteRect.left + flagSize.x;
	spriteRect.bottom = spriteRect.top + flagSize.y;
	scaling.x = 0.2f;
	scaling.y = 0.2f;
	flagTimer = 0;
	flagDuration = 1.0f / 6;
	flagSpeed = (1.0f / flagDuration) * 60;
	flagRow = 0;
	direction.x = 0;
	direction.y = 0;

	position.x = 1 + (rand() % 1280);
	position.y = 1 + (rand() % 1280);
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
	position += velocity;
	if (flagTimer >= flagDuration)
	{
		flagTimer -= flagDuration;
		flagCurrentFrame++;
		flagCurrentFrame %= 2;
	}
	spriteRect.top = flagRow * flagSize.y;
	spriteRect.left = flagSize.x * flagCurrentFrame;
	spriteRect.right = spriteRect.left + flagSize.x;
	spriteRect.bottom = spriteRect.top + flagSize.y;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &position);

}

void flag::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void flag::Release()
{
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
}

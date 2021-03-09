#include "enemy.h"

enemy::enemy()
{
}

enemy::~enemy()
{
}

void enemy::init()
{
	D3DXCreateSprite(GameGraphic::getInstance()->device, &sprite);
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->device, "img/mummy.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);

	enemySize.x = 152;
	enemySize.y = 256;
	enemyCurrentFrame = 0;
	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.right = spriteRect.left + enemySize.x;
	spriteRect.bottom = spriteRect.top + enemySize.y;
	scaling.x = 0.5f;
	scaling.y = 0.5f;
	enemyTimer = 0;
	enemyDuration = 1.0f / 6;
	enemySpeed = (1.0f / enemyDuration) * 60;
	enemyRow = 0;
	isEnemyMoving = false;
	direction.x = 0;
	direction.y = 1;
}

void enemy::Update()
{
	isEnemyMoving = true;
	direction.x += 1;
	direction.y += 1;
}

void enemy::fixedUpdate()
{
	if (isEnemyMoving)
	{
		enemyTimer += 1 / 60.0f;
		D3DXVECTOR2 velocity = direction * (enemySpeed / 60.0f);
		position += velocity;
	}
	if (enemyTimer >= enemyDuration)
	{
		enemyTimer -= enemyDuration;
		enemyCurrentFrame++;
		enemyCurrentFrame %= 4;
	}
	spriteRect.top = enemyRow * enemySize.y;
	spriteRect.left = enemySize.x * enemyCurrentFrame;
	spriteRect.right = spriteRect.left + enemySize.x;
	spriteRect.bottom = spriteRect.top + enemySize.y;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &position);
}

void enemy::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void enemy::Release()
{
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
}

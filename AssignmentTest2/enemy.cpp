#include "enemy.h"

enemy::enemy()
{
	sprite = NULL;
	texture = NULL;
	enemySize.x = 85;
	enemySize.y = 128;
	enemyCurrentFrame = 0;
	enemyRect.top = 0;
	enemyRect.left = 0;
	enemyRect.right = enemyRect.left + enemySize.x;
	enemyRect.bottom = enemyRect.top + enemySize.y;
	scaling.x = 1.0f;
	scaling.y = 1.0f;
	enemyTimer = 0;
	enemyDuration = 3.0f / 6;
	enemySpeed = (1.0f / enemyDuration) * 60;
	enemyRow = 0;
	isEnemyMoving = false;
	for (int i = 0; i < 2; i++)
	{
		enemyPosition[i].x = 1 + (rand() % 1000);
		enemyPosition[i].y = 1 + (rand() % 1000);
		direction.x = 0;
		direction.y = 0;
	}
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
}

void enemy::Update()
{
	isEnemyMoving = false;
	//direction.x = -1;
	//direction.y = -1;
	for (int i = 0; i < 2; i++)
	{
		if (enemyPosition[i].x < -50)
		{
			/*enemyPosition[i].x = -50;*/
			direction.x = 1;
			direction.y = -1;
		}
		else if (enemyPosition[i].x > 1080)
		{
			/*enemyPosition[i].x = 1080;*/
			direction.x = -1;
			direction.y = 1;
		}
		else if (enemyPosition[i].y < 0)
		{
			/*enemyPosition[i].y = 0;*/
			direction.x = -1;
			direction.y = 1;
		}
		else if (enemyPosition[i].y > 1080)
		{
			/*enemyPosition[i].y = 1080;*/
			direction.x = 1;
			direction.y = -1;
		}
	}
}

void enemy::fixedUpdate()
{
	//if (isEnemyMoving)
	//{

	//}
	for (int i = 0; i < 2; i++)
	{
		enemyTimer += 1 / 60.0f;
		D3DXVECTOR2 velocity = direction * (enemySpeed / 60.0f);
		enemyPosition[i] += velocity;
		if (enemyTimer >= enemyDuration)
		{
			enemyTimer -= enemyDuration;
			enemyCurrentFrame++;
			enemyCurrentFrame %= 6;
		}
		enemyRect.top = enemyRow * enemySize.y;
		enemyRect.left = enemySize.x * enemyCurrentFrame;
		enemyRect.right = enemyRect.left + enemySize.x;
		enemyRect.bottom = enemyRect.top + enemySize.y;
	}
}

void enemy::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	for (int i = 0; i < 2; i++)
	{
		sprite->SetTransform(&mat);
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &enemyPosition[i]);
		sprite->Draw(texture, &enemyRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}
	sprite->End();
}

void enemy::Release()
{
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
}

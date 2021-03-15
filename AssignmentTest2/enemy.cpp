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
	direction.x = 0;
	direction.y = 0;
	enemyPosition[0].x = 100;
	enemyPosition[0].y = 100;
	enemyPosition[1].x = 1 + (rand() % 1000);
	enemyPosition[1].y = 1 + (rand() % 1000);
	enemyPosition[2].x = 1 + (rand() % 1000);
	enemyPosition[2].y = 1 + (rand() % 1000);
	enemyPosition[3].x = 1 + (rand() % 1000);
	enemyPosition[3].y = 1 + (rand() % 1000);
	enemyPosition[4].x = 1 + (rand() % 1000);
	enemyPosition[4].y = 1 + (rand() % 1000);
	enemyPosition[5].x = 1 + (rand() % 1000);
	enemyPosition[5].y = 1 + (rand() % 1000);
	enemyPosition[6].x = 1 + (rand() % 1000);
	enemyPosition[6].y = 1 + (rand() % 1000);
	enemyPosition[7].x = 1 + (rand() % 1000);
	enemyPosition[7].y = 1 + (rand() % 1000);
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
	isEnemyMoving = true;
	direction.x = 1;
	direction.y = 1;
	for (int i = 0; i < 7; i++)
	{
		if (enemyPosition[i].x < -50)
		{
			enemyPosition[i].x = -50;
		}
		else if (enemyPosition[i].x > 1080)
		{
			enemyPosition[i].x = 1080;
		}
		else if (enemyPosition[i].y < 0)
		{
			enemyPosition[i].y = 0;
		}
		else if (enemyPosition[i].y > 1080)
		{
			enemyPosition[i].y = 1080;
		}
	}
}

void enemy::fixedUpdate()
{
	//if (isEnemyMoving)
	//{

	//}
	for (int i = 0; i < 7; i++)
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
	for (int i = 0; i < 7; i++)
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

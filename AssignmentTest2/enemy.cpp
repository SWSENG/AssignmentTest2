#include "enemy.h"
#include<iostream>
#include<string>

using namespace std;

enemy::enemy()
{
	sprite = NULL;
	texture = NULL;
	enemySize.x = 85;
	enemySize.y = 128;
	enemyCurrentFrame = 0;
	sampleEnemyRect.top = 0;
	sampleEnemyRect.left = 0;
	sampleEnemyRect.right = sampleEnemyRect.left + enemySize.x;
	sampleEnemyRect.bottom = sampleEnemyRect.top + enemySize.y;
	scaling.x = 1.0f;
	scaling.y = 1.0f;
	enemyTimer = 0;
	enemyDuration = 5.0f / 6;
	enemySpeed = (1.0f / enemyDuration) * 160;
	enemyRow = 0;

	for (int i = 0; i < 5; i++)
	{
		enemyRect[i] = sampleEnemyRect;
	}

	isEnemyMoving = true;
	enemyPosition[0].x = 1 + (rand() % 1000);
	enemyPosition[0].y = 1 + (rand() % 1000);
	direction[0].x = 1;
	direction[0].y = 1;
	enemyPosition[1].x = 1 + (rand() % 1000);
	enemyPosition[1].y = 1 + (rand() % 1000);
	direction[1].x = 1;
	direction[1].y = -1;
	enemyPosition[2].x = 1 + (rand() % 1000);
	enemyPosition[2].y = 1 + (rand() % 1000);
	direction[2].x = -1;
	direction[2].y = 1;
	enemyPosition[3].x = 1 + (rand() % 1000);
	enemyPosition[3].y = 1 + (rand() % 1000);
	direction[3].x = -1;
	direction[3].y = -1;
	enemyPosition[4].x = 1 + (rand() % 1000);
	enemyPosition[4].y = 1 + (rand() % 1000);
	direction[4].x = -1;
	direction[4].y = 1;
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

	for (int i = 0; i < 5; i++)
	{
		if (enemyPosition[i].x < 0)
		{
			enemyPosition[i].x = 0;
			direction[i].x *= -1;
			direction[i].y *= 1;
		}
		else if (enemyPosition[i].x > 1080)
		{
			enemyPosition[i].x = 1080;
			direction[i].x *= -1;
			direction[i].y *= 1;
		}
		else if (enemyPosition[i].y < 0)
		{
			enemyPosition[i].y = 0;
			direction[i].x *= 1;
			direction[i].y *= -1;
		}
		else if (enemyPosition[i].y > 1080)
		{
			enemyPosition[i].y = 1080;
			direction[i].x *= 1;
			direction[i].y *= -1;
		}
	}
}

void enemy::fixedUpdate()
{
	for (int a = 0; a < 5; a++)
	{ 
		for (int b = 0; b < 5; b++)
		{
			if (b == a)
			{
				continue;
			}
			if (checkCollision(enemyPosition[a], enemyRect[a], enemyPosition[b], enemyRect[b]))
			{
				//isEnemyMoving = false;
				D3DXVECTOR2 velocity = direction[a] * (enemySpeed / 60.0f);
				enemyPosition[a] -= velocity;
				enemyPosition[b] -= velocity;
				int i = checkSideOfCollision(enemyPosition[a], enemyPosition[b]);
				//cout << i << endl;

				if (enemyRect[a].bottom > enemyRect[b].top || 
					enemyRect[a].top < enemyRect[b].bottom)
				{
					direction[a].y *= -1;
					direction[b].y *= 1;
					cout << "y axis collide" << endl;
				}
				if (enemyRect[a].right > enemyRect[b].left ||
					enemyRect[a].left < enemyRect[b].right)
				{
					direction[a].x *= -1;
					direction[b].x *= 1;
					cout << "x axis collide" << endl;
				}
			}
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if (isEnemyMoving)
		{
			enemyTimer += 1 / 60.0f;
			D3DXVECTOR2 velocity = direction[i] * (enemySpeed / 60.0f);
			enemyPosition[i] += velocity;
		}
		if (enemyTimer >= enemyDuration)
		{
			enemyTimer -= enemyDuration;
			enemyCurrentFrame++;
			enemyCurrentFrame %= 6;
		}
		enemyRect[i].top = enemyRow * enemySize.y;
		enemyRect[i].left = enemySize.x * enemyCurrentFrame;
		enemyRect[i].right = enemyRect[i].left + enemySize.x;
		enemyRect[i].bottom = enemyRect[i].top + enemySize.y;
	}
}

void enemy::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	for (int i = 0; i < 5; i++)
	{
		sprite->SetTransform(&mat);
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &enemyPosition[i]);
		sprite->Draw(texture, &enemyRect[i], NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
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

bool enemy::checkCollision(D3DXVECTOR2 pos1, RECT rect1, D3DXVECTOR2 pos2, RECT rect2)
{
	rect1.right = pos1.x + rect1.right - rect1.left;
	rect1.left = pos1.x;
	rect1.bottom = pos1.y + rect1.bottom - rect1.top;
	rect1.top = pos1.y;

	rect2.right = pos2.x + rect2.right - rect2.left;
	rect2.left = pos2.x;
	rect2.bottom = pos2.y + rect2.bottom - rect2.top;
	rect2.top = pos2.y;

	if (rect1.bottom < rect2.top) return false;
	if (rect1.top > rect2.bottom) return false;
	if (rect1.right < rect2.left) return false;
	if (rect1.left > rect2.right) return false;

	return true;
}

int enemy::checkSideOfCollision(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2)
{
	D3DXVECTOR2 offset = pos2 - pos1;
	D3DXVec2Normalize(&offset, &offset);

	if (abs(offset.x) > abs(offset.y))
	{
		if (offset.x > 0)
		{
			return 4;
		}
		else
		{
			return 3;
		}
	}
	else
	{
		if (offset.y > 0)
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}

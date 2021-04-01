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

	for (int i = 0; i < 5; i++)
	{
		enemyRect[i] = sampleEnemyRect;
	}

	isEnemyMoving = true;
	enemyPosition[0].x = 10;
	enemyPosition[0].y = 50;
	direction[0].x = 1;
	direction[0].y = 1;
	enemyRow[0] = 0;
	enemyPosition[1].x = 200;
	enemyPosition[1].y = 500;
	direction[1].x = 1;
	direction[1].y = -1;
	enemyRow[1] = 0;
	enemyPosition[2].x = 450;
	enemyPosition[2].y = 20;
	direction[2].x = -1;
	direction[2].y = 1;
	enemyRow[2] = 1;
	enemyPosition[3].x = 700;
	enemyPosition[3].y = 1000;
	direction[3].x = -1;
	direction[3].y = -1;
	enemyRow[3] = 1;
	enemyPosition[4].x = 600;
	enemyPosition[4].y = 50;
	direction[4].x = -1;
	direction[4].y = 1;
	enemyRow[4] = 1;
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
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->device, "img/particle.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &particle_texture);
}

void enemy::Update()
{
	for (int i = 0; i < 5; i++)
	{
		if (enemyPosition[i].x < 0)
		{
			enemyPosition[i].x = 0;
			enemyRow[i] = 0;
			printf("%d\n", enemyRow[i]);
			direction[i].x *= -1;
			direction[i].y *= 1;
		}
		if (enemyPosition[i].x > 1080)
		{
			enemyPosition[i].x = 1080;
			enemyRow[i] = 1;
			direction[i].x *= -1;
			direction[i].y *= 1;
		}
		if (enemyPosition[i].y < 0)
		{
			enemyPosition[i].y = 0;
			//enemyRow[i] = 0;
			direction[i].x *= 1;
			direction[i].y *= -1;
		}
		if (enemyPosition[i].y > 1080)
		{
			enemyPosition[i].y = 1080;
			//enemyRow[i] = 1;
			direction[i].x *= 1;
			direction[i].y *= -1;
		}
	}
	for (int i = 0; i < particleList.size(); i++)
	{
		particleList[i]->update();
	}
}

void enemy::fixedUpdate()
{
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
		enemyRect[i].top = enemyRow[i] * enemySize.y;
		enemyRect[i].left = enemySize.x * enemyCurrentFrame;
		enemyRect[i].right = enemyRect[i].left + enemySize.x;
		enemyRect[i].bottom = enemyRect[i].top + enemySize.y;
	}
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
					direction[a].y *= 1;
					direction[b].y *= -1;
					startParticle(enemyPosition[a]);
					if ((direction[a].x == 1) || (direction[b].x == 1))
					{
						enemyRow[a] = 1;
						enemyRow[b] = 1;
					}
					else
					{
						enemyRow[a] = 0;
						enemyRow[b] = 0;
					}
					cout << "y axis collide" << endl;
				}
				if (enemyRect[a].right > enemyRect[b].left ||
					enemyRect[a].left < enemyRect[b].right)
				{
					direction[a].x *= -1;
					direction[b].x *= 1;
					startParticle(enemyPosition[a]);
					enemyRow[a] = 0;
					enemyRow[b] = 1;
					cout << "x axis collide" << endl;
				}
			}
		}
	}

}

void enemy::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	for (int i = 0; i < 5; i++)
	{
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &enemyPosition[i]);
		sprite->SetTransform(&mat);
		sprite->Draw(texture, &enemyRect[i], NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}
	sprite->End();
	for (int i = 0; i < particleList.size(); i++)
	{
		particleList[i]->draw(sprite, particle_texture);
	}
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

void enemy::startParticle(D3DXVECTOR2 position)
{
	for (int i = 0; i < 1; i++)
	{
		bool foundParticle = false;
		for (int i = 0; i < particleList.size(); i++)
		{
			if (!particleList[i]->isUsing)
			{
				//printf("here\n");
				/*D3DXVECTOR2 pos = D3DXVECTOR2(this->position.x, this->position.y);*/
				particleList[i]->shoot(position);
				foundParticle = true;
			}
		}
		if (!foundParticle)
		{
			for (int i = 0; i < 5; i++)
			{
				/*D3DXVECTOR2 pos = D3DXVECTOR2(, this->position.y);*/
				particle* Particle = new particle();
				Particle->shoot(position);
				particleList.push_back(Particle);
			}
		}

	}
}
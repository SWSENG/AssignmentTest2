#include "gameLevel.h"
#include"gameInput.h"
#include<string>
#include<iostream>
#include"gameStateManager.h"
//#include"collision.h"

using namespace std;

gameLevel::gameLevel()
{
	//collisionObject = new (collision);
	line = NULL;

	score = 10;
	hp = 20;
	scoreFont = NULL;
	hpFont = NULL;

	RECT textRect;
	textRect.left = 100;
	textRect.top = 100;
	textRect.right = 150;
	textRect.bottom = 125;

	RECT textRect2;
	textRect2.left = 100;
	textRect2.top = 100;
	textRect2.right = 150;
	textRect2.bottom = 125;

	font1Position.x = 1120;
	font1Position.y = 20;
	font2Position.x = 150;
	font2Position.y = 40;
}

gameLevel::~gameLevel()
{
}

bool gameLevel::checkCollision(D3DXVECTOR2 pos1, RECT rect1, D3DXVECTOR2 pos2, RECT rect2)
{
	rect1.right = pos1.x + rect1.right - rect1.left+25;
	rect1.left = pos1.x+25;
	rect1.bottom = pos1.y + rect1.bottom - rect1.top;
	rect1.top = pos1.y;

	rect2.right = pos2.x + rect2.right - rect2.left;
	rect2.left = pos2.x;
	rect2.bottom = pos2.y + rect2.bottom - rect2.top;
	rect2.top = pos2.y;

	playerVertices[0] = D3DXVECTOR2(rect1.left, rect1.top);
	playerVertices[1] = D3DXVECTOR2(rect1.right, rect1.top);
	playerVertices[2] = D3DXVECTOR2(rect1.right, rect1.bottom);
	playerVertices[3] = D3DXVECTOR2(rect1.left, rect1.bottom);
	playerVertices[4] = D3DXVECTOR2(rect1.left, rect1.top);

	enemyVertices[0] = D3DXVECTOR2(rect2.left, rect2.top);
	enemyVertices[1] = D3DXVECTOR2(rect2.right, rect2.top);
	enemyVertices[2] = D3DXVECTOR2(rect2.right, rect2.bottom);
	enemyVertices[3] = D3DXVECTOR2(rect2.left, rect2.bottom);
	enemyVertices[4] = D3DXVECTOR2(rect2.left, rect2.top);


	if (rect1.bottom < rect2.top) return false;
	if (rect1.top > rect2.bottom) return false;
	if (rect1.right < rect2.left) return false;
	if (rect1.left > rect2.right) return false;

	cout << "collide" << endl;
	return true;
}

int gameLevel::checkSideOfCollision(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2)
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

void gameLevel::init()
{
	background = new GameBackround();
	background->Initialize(GameGraphic::getInstance()->device, "img/background.png", 1200, 1700);
	drawPlayer = new player();
	drawPlayer->init();
	drawEnemy = new enemy;
	drawEnemy->init();
	drawHeart = new heart();
	drawHeart->init();
	drawFlag = new flag();
	drawFlag->init();
	D3DXCreateLine(GameGraphic::getInstance()->device, &line);
	drawFont = new font();
	drawFont->init();
	D3DXCreateSprite(GameGraphic::getInstance()->device, &sprite);
	D3DXCreateFont(GameGraphic::getInstance()->device, 50, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &scoreFont);

	D3DXCreateSprite(GameGraphic::getInstance()->device, &sprite1);
	D3DXCreateFont(GameGraphic::getInstance()->device, 50, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &hpFont);
}

void gameLevel::Update()
{
	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_ESCAPE))
	{
		PostQuitMessage(0);
	}
	drawPlayer->Update();
	drawEnemy->Update();
	drawFlag->Update();
}

void gameLevel::fixedUpdate()
{
	if (checkCollision(drawPlayer->playerPosition, drawPlayer->spriteSize, drawFlag->flagPosition, drawFlag->flagRect))
	{
		drawFlag->flagPosition.x = 1 + (rand() % 1000);
		drawFlag->flagPosition.y = 1 + (rand() % 1000);
		cout << "flag collide" << endl;
		cout << score << endl;		
		score += 10;
	}
	for (int a = 0; a < 4; a++)
	{
		if (checkCollision(drawPlayer->playerPosition, drawPlayer->spriteSize, drawEnemy->enemyPosition[a], drawEnemy->sampleEnemyRect))
		{
			drawPlayer->isCharacterMoving = false;
			D3DXVECTOR2 velocity = drawPlayer->playerDirection * (drawPlayer->playerSpeed / 60.0f);
			drawPlayer->playerPosition -= velocity;
			cout << "enemy collide" << endl;
			int i = checkSideOfCollision(drawPlayer->playerPosition, drawEnemy->enemyPosition[a]);
			cout << i << endl;
			cout << hp << endl;
			hp -=1;
			if (hp == 0)
			{
				//PostQuitMessage(0);
			}
		}
	}
	drawPlayer->fixedUpdate();
	drawEnemy->fixedUpdate();
	drawFlag->fixedUpdate();
}

void gameLevel::Draw()
{
	background->Draw();
	drawPlayer->Draw();
	drawEnemy->Draw();
	drawHeart->Draw();
	drawFlag->Draw();
	line->Begin();
	line->Draw(playerVertices, 5, D3DCOLOR_XRGB(100, 255, 120));
	line->Draw(enemyVertices, 5, D3DCOLOR_XRGB(100, 255, 120));
	line->End();
	drawFont->Draw();
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);

	string str = to_string(score);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, &font1Position);
	scoreFont->DrawText(sprite, str.c_str(), -1, &textRect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();

	sprite1->Begin(D3DXSPRITE_ALPHABLEND);
	sprite1->SetTransform(&mat1);
	string str2 = to_string(hp);
	D3DXMatrixTransformation2D(&mat1, NULL, 0.0, NULL, NULL, NULL, &font2Position);
	hpFont->DrawText(sprite1, str2.c_str(), -1, &textRect2, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	sprite1->End();
}

void gameLevel::Release()
{
	sprite1->Release();
	sprite1 = NULL;
	hpFont->Release();
	hpFont = NULL;

	sprite->Release();
	sprite = NULL;
	scoreFont->Release();
	scoreFont = NULL;
	drawFont->Release();
	if (drawFont) { delete drawFont; drawFont = nullptr; }
	line->Release();
	line = NULL;
	drawFlag->Release();
	if (drawFlag) { delete drawFlag; drawFlag = nullptr; }
	drawHeart->Release();
	if (drawHeart) { delete drawHeart; drawHeart = nullptr; }
	drawEnemy->Release();
	if (drawEnemy) { delete drawEnemy; drawEnemy = nullptr; }
	drawPlayer->Release();
	if (drawPlayer) { delete drawPlayer; drawPlayer = nullptr; }
	background->~GameBackround();
	if (background) { delete background; background = nullptr; }
}
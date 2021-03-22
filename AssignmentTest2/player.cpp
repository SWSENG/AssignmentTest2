#include "player.h"
#include"gameInput.h"
#include<string>
#include <iostream>

using namespace std;

player::player()
{
	sprite = NULL;
	texture = NULL;
	characterSize.x = 114;
	characterSize.y = 128;
	spriteSize.top = 0;
	spriteSize.left = 0;
	spriteSize.right = 55;
	spriteSize.bottom = 115;
	characterCurrentFrame = 0;
	playerRect.top = 0;
	playerRect.left = 0;
	playerRect.right = playerRect.left + characterSize.x;
	playerRect.bottom = playerRect.top + characterSize.y;
	scaling.x = 1.0f;
	scaling.y = 1.0f;
	animationTimer = 0;
	animationDuration = 1.0f / 9;
	playerSpeed = (1.0f / animationDuration) * 60;
	animationRow = 0;
	isCharacterMoving = false;
	playerDirection.x = 0;
	playerDirection.y = 1;
	playerPosition.x = 500;
	playerPosition.y = 500;
	playerCenter.x = 57;
	playerCenter.y = 64;
}

player::~player()
{
}

void player::init()
{
	D3DXCreateSprite(GameGraphic::getInstance()->device, &sprite);
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->device, "img/PlayerWalk.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);
}

void player::Update()
{
	//Player movement update
	if (GameInput::getInstance()->KeyboardKeyHold(DIK_LEFT))
	{
		animationRow = 1;
		isCharacterMoving = true;
		playerDirection.x = -1;
		playerDirection.y = 0;
	}
	else if (GameInput::getInstance()->KeyboardKeyHold(DIK_UP))
	{
		animationRow = 0;
		isCharacterMoving = true;
		playerDirection.x = 0;
		playerDirection.y = -1;
	}
	else if (GameInput::getInstance()->KeyboardKeyHold(DIK_RIGHT))
	{
		animationRow = 3;
		isCharacterMoving = true;
		playerDirection.x = 1;
		playerDirection.y = 0;
	}
	else if (GameInput::getInstance()->KeyboardKeyHold(DIK_DOWN))
	{
		animationRow = 2;
		isCharacterMoving = true;
		playerDirection.x = 0;
		playerDirection.y = 1;
	}
	else
	{
		isCharacterMoving = false;
	}
	if (playerPosition.x < 0)
	{
		playerPosition.x = 0;
	}
	else if (playerPosition.x > 1080)
	{
		playerPosition.x = 1080;
	}
	else if (playerPosition.y < 0)
	{
		playerPosition.y = 0;
	}
	else if (playerPosition.y > 1080)
	{
		playerPosition.y = 1080;
	}
	//cout << playerPosition.x << "  " << playerPosition.y << endl;
}

void player::fixedUpdate()
{
	//Player update
	if (isCharacterMoving)
	{
		animationTimer += 1 / 60.0f;
		D3DXVECTOR2 velocity = playerDirection * (playerSpeed / 60.0f);
		playerPosition += velocity;
	}
	if (animationTimer >= animationDuration)
	{
		animationTimer -= animationDuration;
		characterCurrentFrame++;
		characterCurrentFrame %= 4;
	}
	playerRect.top = animationRow * characterSize.y;
	playerRect.left = characterSize.x * characterCurrentFrame;
	playerRect.right = playerRect.left + characterSize.x;
	playerRect.bottom = playerRect.top + characterSize.y;
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &playerPosition);
}

void player::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &playerRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void player::Release()
{
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
}
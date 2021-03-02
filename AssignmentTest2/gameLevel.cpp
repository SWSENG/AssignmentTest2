#include "gameLevel.h"
#include"gameInput.h"
#include<string>
#include<iostream>
#include"gameStateManager.h"

using namespace std;

gameLevel::gameLevel()
{
	sprite = NULL;
	texture = NULL;
}

gameLevel::~gameLevel()
{
}

void gameLevel::init()
{

	D3DXCreateSprite(GameGraphic::getInstance()->device, &sprite);
	D3DXCreateTextureFromFileEx(GameGraphic::getInstance()->device, "img/PlayerWalk.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture);

	characterSize.x = 56;
	characterSize.y = 60;
	characterCurrentFrame = 0;


	spriteRect.top = 0;
	spriteRect.left = 0;
	spriteRect.right = spriteRect.left + characterSize.x;
	spriteRect.bottom = spriteRect.top + characterSize.y;

	scaling.x = 2.5f;
	scaling.y = 2.5f;

	animationTimer = 0;
	animationDuration = 1.0f / 9;
	speed = (1.0f / animationDuration) * 80;
	animationRow = 0;

	isCharacterMoving = false;
	direction.x = 0;
	direction.y = 1;
}

void gameLevel::Update()
{
	if (GameInput::getInstance()->KeyboardKeyPressed(DIK_LEFT))
	{
		animationRow = 2;
		isCharacterMoving = true;
		direction.x = 0;
		direction.y = 1;
	}
	else if (GameInput::getInstance()->KeyboardKeyPressed(DIK_UP))
	{
		animationRow = 1;
		isCharacterMoving = true;
		direction.x = -1;
		direction.y = 0;
	}
	else if (GameInput::getInstance()->KeyboardKeyPressed(DIK_RIGHT))
	{
		animationRow = 0;
		isCharacterMoving = true;
		direction.x = 0;
		direction.y = -1;
	}
	else if (GameInput::getInstance()->KeyboardKeyPressed(DIK_DOWN))
	{
		animationRow = 3;
		isCharacterMoving = true;
		direction.x = 1;
		direction.y = 0;
	}
	else
	{
		isCharacterMoving = false;
	}
}

void gameLevel::fixedUpdate()
{
	if (isCharacterMoving)
	{
		animationTimer += 1 / 60.0f;
		D3DXVECTOR2 velocity = direction * (speed / 60.0f);
		position += velocity;
	}
	
	if (animationTimer >= animationDuration)
	{
		animationTimer -= animationDuration;
		characterCurrentFrame++;
		characterCurrentFrame %= 4;
	}

	spriteRect.top = animationRow * characterSize.y;
	spriteRect.left = characterSize.x * characterCurrentFrame;
	spriteRect.right = spriteRect.left + characterSize.x;
	spriteRect.bottom = spriteRect.top + characterSize.y;

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &position);
}

void gameLevel::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();

}

void gameLevel::Release()
{
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
}
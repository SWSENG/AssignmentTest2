#include "font.h"

font::font()
{
	scoreFont = NULL;
	heartFont = NULL;

	RECT textRect;
	textRect.left = 100;
	textRect.top = 100;
	textRect.right = 150;
	textRect.bottom = 125;

	font1Position.x = 1000;
	font1Position.y = 20;
}

font::~font()
{
}

void font::init()
{
	D3DXCreateSprite(GameGraphic::getInstance()->device, &sprite);
	D3DXCreateFont(GameGraphic::getInstance()->device, 50, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &scoreFont);
}

void font::Update()
{

}

void font::Draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->SetTransform(&mat);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, &font1Position);
	scoreFont->DrawText(sprite, "Score: ", -1, &textRect, DT_CENTER | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
	sprite->End();
}

void font::Release()
{
	sprite->Release();
	sprite = NULL;
	scoreFont->Release();
	scoreFont = NULL;
}
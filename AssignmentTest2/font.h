#pragma once
#include"gameGraphic.h"

class font
{
private:
	LPD3DXFONT scoreFont;
	LPD3DXFONT heartFont;
	RECT textRect;
	LPD3DXSPRITE sprite;
	D3DXVECTOR2 font1Position;
	D3DXMATRIX mat;

public:
	font();
	~font();
	void init();
	void Update();
	void Draw();
	void Release();
};

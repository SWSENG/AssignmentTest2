#pragma once
#include"gameGraphic.h"

class particle
{
public:
	D3DXVECTOR2 position;
	D3DXVECTOR2 velocity;
	D3DXMATRIX mat;
	float alpha;
	bool isUsed;

	particle();
	~particle();
	bool isUsing;
	void shoot(D3DXVECTOR2 startPosition);
	void update();
	void draw(LPD3DXSPRITE sprite, LPDIRECT3DTEXTURE9 texture);
};


#pragma once
#include"gameGraphic.h"

class heart
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	RECT heartRect;
	D3DXMATRIX mat;
	float rotation = 0;
	int x = 0;
	float directionX = 1;
	D3DXVECTOR2 spriteCentre;
	D3DXVECTOR2 heartPosition;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 heartSize;
	D3DXVECTOR2 direction;

public:
	heart();
	~heart();

	void init();
	void Update();
	void fixedUpdate();
	void Draw();
	void Release();
};


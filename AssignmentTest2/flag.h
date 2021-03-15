#pragma once
#include"gameGraphic.h"

class flag
{
private:
	LPDIRECT3DTEXTURE9 texture;
	LPD3DXSPRITE sprite;
	D3DXMATRIX mat;
	D3DXVECTOR2 spriteCentre;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 flagSize;
	int flagCurrentFrame;
	float flagDuration;
	float flagTimer;
	int flagRow;
	float flagSpeed;
	D3DXVECTOR2 direction;

public:
	flag();
	~flag();
	RECT flagRect;
	D3DXVECTOR2 flagPosition;

	void init();
	void Update();
	void fixedUpdate();
	void Draw();
	void Release();
};


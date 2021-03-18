#pragma once
#include"gameGraphic.h"

class collision
{
public:
	virtual bool checkCollision(D3DXVECTOR2 pos1, RECT rect1, D3DXVECTOR2 pos2, RECT rect2) = 0;
	virtual int checkSideOfCollision(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2) = 0;

private:
	LPD3DXLINE line;
};
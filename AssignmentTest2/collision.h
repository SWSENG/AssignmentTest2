#pragma once
#include"gameGraphic.h"
#include"player.h"

class collision
{
public:
	collision();
	~collision();
	virtual bool checkCollision(D3DXVECTOR2 pos1, RECT rect1, D3DXVECTOR2 pos2, RECT rect2);
	int checkSideOfCollision(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2);

private:
	LPD3DXLINE line;
};

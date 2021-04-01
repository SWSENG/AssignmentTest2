#pragma once
#include<vector>
#include"gameGraphic.h"

class effect
{
private:
	LPDIRECT3DTEXTURE9 texture;
	D3DXVECTOR2 position;
	D3DXMATRIX mat;

	static std::vector<effect*>poolList;
	effect();
	~effect();

	
	void create(LPDIRECT3DTEXTURE9 texture);
	void release();
public:
	bool isUsing;
	static effect* getEffect(LPDIRECT3DTEXTURE9 texture);
	static void releaseAllEffect();

	void init(D3DXVECTOR2 position);
	void draw(LPD3DXSPRITE sprite);
	void hide();
	void update();


};


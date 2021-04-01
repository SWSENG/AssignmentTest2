#include "effect.h"

std::vector<effect*>effect::poolList;
effect* effect::getEffect(LPDIRECT3DTEXTURE9 texture)
{
	effect* Effect = NULL;
	for (int i = 0; i < poolList.size(); i++)
	{
		if (poolList[i]->isUsing == false)
		{
			Effect = poolList[i];
			break;
		}
	}
	if (Effect == NULL)
	{
		Effect = new effect;
		Effect->create(texture);
		poolList.push_back(Effect);
	}
	return Effect;
}

void effect::releaseAllEffect()
{
	for (int i = 0; i < poolList.size(); i++)
	{
		poolList[i]->release();
		delete poolList[i];
		poolList[i] = NULL;
	}
	poolList.clear();
}

effect::effect()
{
	isUsing = false;
}

effect::~effect()
{
}

void effect::create(LPDIRECT3DTEXTURE9 texture)
{
	this->texture = texture;
}

void effect::init(D3DXVECTOR2 position)
{
	this->position = position;
}

void effect::draw(LPD3DXSPRITE sprite)
{
	if (isUsing == false)
	{
		return;
	}
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, &position);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
}

void effect::hide()
{
	isUsing = false;
}

void effect::update()
{
	if (isUsing == false)
	{
		return;
	}
}

void effect::release()
{
}

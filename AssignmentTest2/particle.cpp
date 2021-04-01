#include "particle.h"

particle::particle()
{
}

particle::~particle()
{
}

void particle::shoot(D3DXVECTOR2 startPosition)
{
	isUsing = true;
	position = startPosition;

	int angle = rand() % 360;
	D3DXVECTOR2 direction;
	direction.x = sin(angle / 180. * 3.14159);
	direction.y = -cos(angle / 180. * 3.14159);
	D3DXVec2Normalize(&direction, &direction);

	alpha = 255;
	velocity = direction * (rand() % 100 + 100) * 2;
}

void particle::update()
{
	if (isUsing)
	{
		velocity.y += 200 * 1 / 60.0f;
		position += (velocity * 1 / 60.0f);
		alpha -= (300 * 1 / 60.0f);
		alpha = max(alpha, 0);
	}
	else if (position.x > 400 || position.x < 0 || position.y < 0 || position.y>300)
	{
		isUsing = false;
	}
}

void particle::draw(LPD3DXSPRITE sprite, LPDIRECT3DTEXTURE9 texture)
{
	if (isUsing)
	{
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, &position);
		sprite->SetTransform(&mat);
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_ARGB((int)alpha, 255, 255, 255));
		sprite->End();
	}
}

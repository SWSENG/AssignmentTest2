#ifndef GAMESPRITE_H
#define GAMESPRITE_H

//Texture and Sprites and other functions.
#include <d3dx9.h>
#include <string>
#include "gameTime.h"

class GameSprite
{
public:
	//Attributes
	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity;

	//Constructors and Destructor
	GameSprite();
	GameSprite(float x, float y, float s);
	~GameSprite();
	//void updateFrame(int frame);
	//Sprite Functions
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height);
	bool IsInitialized();
	virtual void HandleInput();
	virtual void Update(float gameTime);
	virtual void Draw(float gameTime);
private:
	//Pointers
	LPDIRECT3DTEXTURE9 tex;
	LPD3DXSPRITE sprite;

	//Attributes
	D3DCOLOR color;
	bool initialized;
	float speed;
	//GameTime* gameTime;
};

#endif /* GAMESPRITE_H */
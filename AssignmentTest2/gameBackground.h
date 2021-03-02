#ifndef GAMEBACKGROUND_H
#define GAMEBACKGROUND_H
#include <d3dx9.h>
#include <string>

class GameBackround
{
public:
	//Attributes
	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity;

	//Constructors and Destructor
	GameBackround();
	~GameBackround();
	//Sprite Functions
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height);
	bool IsInitialized();
	virtual void Draw(float gameTime);
private:
	//Pointers
	LPDIRECT3DTEXTURE9 tex;
	LPD3DXSPRITE background;

	//Attributes
	D3DCOLOR color;
	bool initialized;
	//GameTime* gameTime;
};

#endif
//#include "GameSprite.h"
//
//GameSprite::GameSprite()
//{
//	//Default the sprite to position (0, 0, 0)
//	position.x = 0;
//	position.y = 0;
//	position.z = 0;
//
//	//When color is set to white, what you see is exactly what the image looks like.
//	color = D3DCOLOR_ARGB(255, 255, 255, 255);
//
//	speed = 0;
//
//	//We are not initialized yet
//	initialized = false;
//}
//
//GameSprite::GameSprite(float x, float y, float s)
//{
//	//Set the position to the programmer's requested X and Y coordinates.  
//	//Default Z to 0
//	position.x = x;
//	position.y = y;
//	position.z = 0;
//
//	speed = s;
//
//	velocity.x = 0;
//	velocity.y = 0;
//	velocity.z = 0;
//
//	//When color is set to white, what you see is exactly what the image looks like.
//	color = D3DCOLOR_ARGB(255, 255, 255, 255);
//
//	//We are not initialized yet
//	initialized = false;
//}
//
//bool GameSprite::Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height)
//{
//	//Same functionality as D3DXCreateTextureFromFile EXCEPT width and height are manually entered
//	if (!SUCCEEDED(D3DXCreateTextureFromFileEx(device, file.c_str(),
//		width, height, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT,
//		D3DX_DEFAULT, 0, NULL, NULL, &tex)))
//	{
//		std::string s = "There was an issue creating the Texture.  Make sure the requested image is available.  Requested image: " + file;
//		MessageBox(NULL, s.c_str(), NULL, NULL);
//		return false;
//	}
//
//	//Attempt to create the sprite
//	if (!SUCCEEDED(D3DXCreateSprite(device, &sprite)))
//	{
//		MessageBox(NULL, "There was an issue creating the Sprite.", NULL, NULL);
//		return false;
//	}
//
//	initialized = true;
//
//	return true;
//}
//
//bool GameSprite::IsInitialized()
//{
//	//Are we initialized (have a texture and sprite)
//	return initialized;
//}
//
//void GameSprite::HandleInput()
//{
//	D3DXVECTOR3 movementVector(0, 0, 0);
//
//	if (GetAsyncKeyState(VK_UP))
//	{
//		movementVector.y -= 1;
//	}
//	if (GetAsyncKeyState(VK_DOWN))
//	{
//		movementVector.y += 1;
//	}
//
//	if (GetAsyncKeyState(VK_LEFT))
//	{
//		movementVector.x -= 1;
//	}
//	if (GetAsyncKeyState(VK_RIGHT))
//	{
//		movementVector.x += 1;
//	}
//
//	if (movementVector.x != 0 || movementVector.y != 0)
//	{
//		float angle = atan2(movementVector.y, movementVector.x);
//
//		velocity.x = speed * cos(angle);
//		velocity.y = speed * sin(angle);
//	}
//	else
//	{
//		velocity.x = 0;
//		velocity.y = 0;
//	}
//}
//
//void GameSprite::Update(float gameTime)
//{
//	position.x += velocity.x * gameTime;
//	position.y += velocity.y * gameTime;
//
//	//No need to update Z since it is 2D.  Make sure it is 0.
//	position.z = 0;
//}
//
//int spriteIndex = 0;
//void GameSprite::Draw(float gameTime)
//{
//	int width = 40;
//	int height = 70;
//
//	RECT clipWindow[4];
//	clipWindow[0].top = 0;
//	clipWindow[0].left = 0;
//	clipWindow[0].bottom = 100;
//	clipWindow[0].right = 40;
//	clipWindow[1].top = 0;
//	clipWindow[1].left = 40;
//	clipWindow[1].bottom = 100;
//	clipWindow[1].right = 80;
//	clipWindow[2].top = 0;
//	clipWindow[2].left = 80;
//	clipWindow[2].bottom = 100;
//	clipWindow[2].right = 120;
//	clipWindow[3].top = 0;
//	clipWindow[3].left = 120;
//	clipWindow[3].bottom = 100;
//	clipWindow[3].right = 180;
//
//	spriteIndex++;
//	spriteIndex %= 4;
//
//	//updateFrame(60);
//	if (sprite && tex)
//	{
//		//D3DXSPRITE_OBJECTSPACE is needed for the camera to work
//		sprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
//
//		sprite->Draw(tex, &clipWindow[spriteIndex], NULL, &position, color);
//
//		sprite->End();
//	}
//}
//
//void GameSprite::updateFrame(int no)
//{
//	int frame = gameTime->framesToUpdate();
//	for (int i = 0; i < frame; i++)	{
//		spriteIndex++;
//		spriteIndex %= 4;
//	}
//}
//
//GameSprite::~GameSprite()
//{
//	if (sprite)
//	{
//		sprite->Release();
//		sprite = 0;
//	}
//
//	if (tex)
//	{
//		tex->Release();
//		tex = 0;
//	}
//}
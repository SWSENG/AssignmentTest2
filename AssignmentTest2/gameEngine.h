#pragma once
#ifndef GAME_H
#define GAME_H

#include "gameGraphic.h"
#include "gameSprite.h"
#include "gameTime.h"
#include "gameCamera.h"

class Game
{
public:
	//Constructors and Destructor
	Game();
	~Game();

	//Game Functions
	bool Initialize(HWND hWnd, int width, int height);
	void Run();
	void Update(float gameTime);
	void Draw(float gameTime);
private:
	Camera* camera;

	GraphicsDevice* gDevice;

	GameSprite* background;
	GameSprite* player;
	GameTime* gameTime;


	int width;
	int height;
};

#endif /* GAME_H */
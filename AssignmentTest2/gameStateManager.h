#pragma once
#include"gameState.h"
#include<vector>
#include"gameTime.h"

class gameStateManager
{
private:
	static gameStateManager* sInstance;
	std::vector<gameState*> gameStateList;
	gameState* currentGameState;

	GameTime* gametimer = NULL;
public:
	enum GAMESTATENAME {
		MAIN,
		TUTORIAL,
		LEVEL,
		GAMEOVER
	};
	static gameStateManager* getInstance();
	static void releaseInstance();

	gameStateManager();
	~gameStateManager();

	void Update();
	void Draw();
	void changeGameState(int index);
};


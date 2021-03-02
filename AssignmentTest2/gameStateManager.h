#pragma once
#include"gameState.h"
#include<vector>
#include"gameTime.h"

class gameStateManager
{
private:
	gameStateManager();
	~gameStateManager();

	static gameStateManager* sInstance;
	std::vector<gameState*> gameStateList;
	gameState* currentGameState;

	GameTime* gametimer = NULL;
public:
	enum GAMESTATENAME {
		MAIN,
		LEVEL
	};
	static gameStateManager* getInstance();
	static void releaseInstance();

	void Update();
	void Draw();
	void changeGameState(int index);
};


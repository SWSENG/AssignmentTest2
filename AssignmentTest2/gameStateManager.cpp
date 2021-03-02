#include "gameStateManager.h"
#include"gameLevel.h"

gameStateManager::gameStateManager()
{
	gameLevel* level = new gameLevel();
	level->init();
	gameStateList.push_back(level);

	currentGameState = level;

	gametimer = new GameTime();
	gametimer->init(120);
}

gameStateManager::~gameStateManager()
{
	for (int i = 0; i < gameStateList.size(); i++)
	{
		delete gameStateList[i];
		gameStateList[i] = NULL;
	}

	delete gametimer;
	gametimer = NULL;
}

gameStateManager* gameStateManager::sInstance = 0;

gameStateManager* gameStateManager::getInstance()
{
	if (sInstance == 0)
	{
		sInstance = new gameStateManager();
	}
	return sInstance;
}

void gameStateManager::releaseInstance()
{
	if (sInstance != 0)
	{
		delete sInstance;
		sInstance = 0;
	}
}

void gameStateManager::changeGameState(int index)
{
	currentGameState = gameStateList[index];
}

void gameStateManager::Update()
{
	int frameToUpdate = gametimer->framesToUpdate();
	for (int i = 0; i < frameToUpdate; i++)
	{
		currentGameState->Update();
	}

}

void gameStateManager::Draw()
{
	currentGameState->Draw();
}
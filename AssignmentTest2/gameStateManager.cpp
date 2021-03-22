#include "gameStateManager.h"
#include"gameLevel.h"
#include"menu.h"
#include"tutorial.h"
#include"gameOver.h"

gameStateManager::gameStateManager()
{
	gameMenu* firstpage = new gameMenu();
	firstpage->init();
	tutorial* tutorialpage = new tutorial();
	tutorialpage->init();
	gameLevel* level = new gameLevel();
	level->init();
	gameOver* gameOverpage = new gameOver();
	gameOverpage->init();

	gameStateList.push_back(firstpage);
	gameStateList.push_back(tutorialpage);
	gameStateList.push_back(level);
	gameStateList.push_back(gameOverpage);

	currentGameState = firstpage;

	gametimer = new GameTime();
	gametimer->init(40);
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
	currentGameState->Update();
	int frameToUpdate = gametimer->framesToUpdate();
	for (int i = 0; i < frameToUpdate; i++)
	{
		currentGameState->fixedUpdate();
	}

}

void gameStateManager::Draw()
{
	currentGameState->Draw();
}
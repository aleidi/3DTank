#include <assert.h>

#include "GameLevelManager.h"
#include "GameLevelBase.h"

GameLevelManager* GameLevelManager::sInstance = nullptr;

GameLevelManager * GameLevelManager::sGetInstance()
{
	return sInstance;
}

void GameLevelManager::createSingleton()
{
	assert(!sInstance);
	sInstance = new GameLevelManager();
}

void GameLevelManager::destroy()
{
	delete sInstance;
	sInstance = nullptr;
}

bool GameLevelManager::onInit()
{

	return true;
}

bool GameLevelManager::onUpdadte(float deltaTime)
{
	mCurrentLevel->onUpdate(deltaTime);
	return true;
}

bool GameLevelManager::ChangeLevel(GameLevelBase * level)
{
	if (mCurrentLevel == level)
	{
		return false;
	}

	mCurrentLevel->leaveLevel();
	mCurrentLevel = level;
	mCurrentLevel->enterLevel();
	
	return true;
}

GameLevelManager::GameLevelManager()
{
}

GameLevelManager::~GameLevelManager()
{
	delete mCurrentLevel;
	mCurrentLevel = nullptr;
}

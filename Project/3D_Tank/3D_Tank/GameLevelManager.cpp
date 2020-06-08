#include <assert.h>

#include "GameLevelManager.h"

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
	return true;
}

GameLevelManager::GameLevelManager()
{
}

GameLevelManager::~GameLevelManager()
{
}

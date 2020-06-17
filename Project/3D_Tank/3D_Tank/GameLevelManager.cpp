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
	if (nullptr == mCurrentLevel)
	{
		return false;
	}

	GameLevelBase* nextLevel = mCurrentLevel->onUpdate(deltaTime);
	if (nextLevel != mCurrentLevel)
	{
		mCurrentLevel->leaveLevel();
		mCurrentLevel = nextLevel;
		if (mCurrentLevel != nullptr)
		{
			mCurrentLevel->enterLevel();
		}
	}

	return true;
}

void GameLevelManager::addLevel(int id, GameLevelBase * level)
{
	if (mLevels.find(id) != mLevels.end())
	{
		delete mLevels[id];
	}
	mLevels[id] = level;
}

GameLevelBase* GameLevelManager::changeLevel(int id)
{
	if (mLevels.find(id) != mLevels.end())
	{
		return mLevels.at(id);
	}
	return nullptr;
}

void GameLevelManager::setDefaultLevel(int id)
{
	if (mLevels.find(id) != mLevels.end())
	{
		mCurrentLevel = mLevels.at(id);
		mCurrentLevel->enterLevel();
	}
}

GameLevelManager::GameLevelManager()
	:mLevels()
{
}

GameLevelManager::~GameLevelManager()
{
	delete mCurrentLevel;
	mCurrentLevel = nullptr;
}

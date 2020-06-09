#pragma once

#include "GameCommon.h"

class GameLevelBase;

class GameLevelManager
{
public:
	static GameLevelManager* sGetInstance();
	static void createSingleton();
	static void destroy();

	bool onInit();
	bool onUpdadte(float deltaTime);
	void addLevel(int id, GameLevelBase* level);
	GameLevelBase* changeLevel(int id);
	void setDefaultLevel(int id);

private:
	GameLevelManager();
	~GameLevelManager();

private:
	static GameLevelManager* sInstance;
	
	GameLevelBase* mCurrentLevel;
	std::map<int, GameLevelBase*> mLevels;
};


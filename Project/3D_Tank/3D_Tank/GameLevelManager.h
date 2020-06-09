#pragma once

class GameLevelBase;

class GameLevelManager
{
public:
	static GameLevelManager* sGetInstance();
	static void createSingleton();
	static void destroy();

	bool onInit();
	bool onUpdadte(float deltaTime);
	bool ChangeLevel(GameLevelBase* level);

private:
	GameLevelManager();
	~GameLevelManager();

private:
	static GameLevelManager* sInstance;
	
	GameLevelBase* mCurrentLevel;
};


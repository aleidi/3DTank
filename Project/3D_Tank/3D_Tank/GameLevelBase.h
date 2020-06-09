#pragma once

#include "GameModeBase.h"
#include "GameLevelManager.h"

class GameLevelBase
{
public:
	GameLevelBase() = default;
	virtual ~GameLevelBase() {}

	virtual void enterLevel() = 0;
	virtual GameLevelBase* onUpdate(float deltaTime) = 0;
	virtual void leaveLevel() = 0;

	void setGameMode(GameModeBase* gameMode)
	{
		mCurrentGameMode = gameMode;
	}

	GameModeBase* getGameMode()
	{
		return mCurrentGameMode;
	}
	
protected:
	GameModeBase* mCurrentGameMode;
};


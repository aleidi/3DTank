#pragma once

class GameModeBase;

class GameLevelBase
{
public:
	GameLevelBase();
	virtual ~GameLevelBase()
	{
		delete mCurrentGameMode;
		mCurrentGameMode = nullptr;
	}

	virtual bool enterLevel() = 0;
	virtual bool onUpdate(float deltaTime) = 0;
	virtual bool leaveLevel() = 0;

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


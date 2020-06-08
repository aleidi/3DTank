#pragma once

class GameModeBase;

class GameLevelBase
{
public:
	GameLevelBase();
	~GameLevelBase();
	
protected:
	GameModeBase* mCurrentGameMode;
};


#include "Level01.h"

Level01::Level01()
{
	GameLevelManager::sGetInstance()->addLevel(1, this);
}

Level01::~Level01()
{
}

void Level01::enterLevel()
{
}

GameLevelBase * Level01::onUpdate(float deltaTime)
{
	if (mCurrentGameMode != nullptr)
	{
	}
	return this;
}

void Level01::leaveLevel()
{
}

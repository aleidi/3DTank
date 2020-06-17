#include "Level02.h"

Level02::Level02()
{
	GameLevelManager::sGetInstance()->addLevel(2, this);
}

Level02::~Level02()
{
}

void Level02::enterLevel()
{
}

GameLevelBase * Level02::onUpdate(float deltaTime)
{
	return this;
}

void Level02::leaveLevel()
{
}

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
	mCurrentGameMode = new GameModeBase();
	mCurrentGameMode->onInit();

	mMap = SceneManager::sGetInstance()->createEmptyObject();
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/TownStreet", L"Wall");
}

GameLevelBase * Level02::onUpdate(float deltaTime)
{
	SceneManager::sGetInstance()->onUpdate(deltaTime);

	return this;
}

void Level02::leaveLevel()
{
}

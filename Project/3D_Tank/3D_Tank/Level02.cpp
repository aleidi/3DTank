#include "Level02.h"
#include "AITank.h"
#include "GameModeTP.h"

Level02::Level02()
{
	GameLevelManager::sGetInstance()->addLevel(2, this);
}

Level02::~Level02()
{
}

void Level02::enterLevel()
{
	//mCurrentGameMode = new GameModeBase();
	//mCurrentGameMode->onInit();
	mCurrentGameMode = new GameModeTP();

	mMap = SceneManager::sGetInstance()->createEmptyObject();
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/TownStreet", L"Objects/Wall");
	mMap->getTransform()->setScale(0.1f, 0.1f, 0.1f);
	new AITank(0);
}

GameLevelBase * Level02::onUpdate(float deltaTime)
{
	SceneManager::sGetInstance()->onUpdate(deltaTime);
	SceneManager::sGetInstance()->onLateUpdate(deltaTime);

	return this;
}

void Level02::leaveLevel()
{
}

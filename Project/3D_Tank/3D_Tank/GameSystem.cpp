#include "GameSystem.h"
#include "SceneManager.h"
#include "GameLevelTest.h"
#include "GameLevelManager.h"

GameSystem::GameSystem()
{
	GameLevelManager::sGetInstance()->createSingleton();
}

GameSystem::~GameSystem()
{
}

void GameSystem::onInit()
{
	GameLevelTest* level = new GameLevelTest();
	GameLevelManager::sGetInstance()->setDefaultLevel(0);
	
}

void GameSystem::onUpdate(float deltaTime)
{
	GameLevelManager::sGetInstance()->onUpdadte(deltaTime);
	//SceneManager::sGetInstance ()->onUpdate(deltaTime);
}

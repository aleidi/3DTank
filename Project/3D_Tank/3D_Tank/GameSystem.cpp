#include "GameSystem.h"
#include "SceneManager.h"
#include "GameLevelTest.h"
#include "Level01.h"
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
	new Level01();
	GameLevelManager::sGetInstance()->setDefaultLevel(0);
	
}

void GameSystem::onUpdate(float deltaTime)
{
	GameLevelManager::sGetInstance()->onUpdadte(deltaTime);
	//SceneManager::sGetInstance ()->onUpdate(deltaTime);
}

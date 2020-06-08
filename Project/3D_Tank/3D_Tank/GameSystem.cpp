#include "GameSystem.h"
#include "SceneManager.h"

GameSystem::GameSystem()
{
}

GameSystem::~GameSystem()
{
}

void GameSystem::onInit()
{
}

void GameSystem::onUpdate(float deltaTime)
{
	SceneManager::sGetInstance()->onUpdate(deltaTime);
}

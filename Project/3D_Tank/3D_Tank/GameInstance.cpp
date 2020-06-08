#include <assert.h>

#include "GameInstance.h"
#include "GameInput.h"
#include "GameLevelManager.h"

GameInstance* GameInstance::sInstance = nullptr;

GameInstance * GameInstance::sGetInstance()
{
	return sInstance;
}

void GameInstance::createSingleton()
{
	assert(!sInstance);
	sInstance = new GameInstance();
}

void GameInstance::Destroy()
{
	delete sInstance;
	sInstance = nullptr;
}

bool GameInstance::onInit()
{
	GameInput::sGetInstance()->onInit();
	GameLevelManager::sGetInstance()->onInit();

	return true;
}

bool GameInstance::onUpdate(float deltaTime)
{
	GameInput::sGetInstance()->onUpdate(deltaTime);
	GameLevelManager::sGetInstance()->onUpdadte(deltaTime);

	return true;
}

GameInstance::GameInstance()
{
	GameInput::creataSingleton();
	GameLevelManager::createSingleton();
}

GameInstance::~GameInstance()
{
}

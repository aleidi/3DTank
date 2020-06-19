#include <assert.h>

#include "GameInstance.h"
#include "GameInput.h"
#include "GameLevelManager.h"
#include "GameModeBase.h"

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
	//GameInput::sGetInstance()->onInit();

	return true;
}

bool GameInstance::onUpdate(float deltaTime)
{
	//GameInput::sGetInstance()->onUpdate(deltaTime);

	return true;
}

Pawn * GameInstance::getPlayer()
{
	return GameModeBase::MainGameMode->getPlayer();
}

ControllerBase * GameInstance::getPlayerController()
{
	return GameModeBase::MainGameMode->getPlayerController();
}

GameInstance::GameInstance()
{
	//GameInput::creataSingleton();
	//GameLevelManager::createSingleton();
}

GameInstance::~GameInstance()
{
}

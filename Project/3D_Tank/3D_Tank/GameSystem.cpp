#include "GameSystem.h"
#include "SceneManager.h"
#include "GameLevelTest.h"
#include "Level01.h"
#include "Level02.h"
#include "Level03.h"
#include "GameLevelManager.h"
#include "GameInstance.h"
#include "DisplayManager.h"
#include "CameraShake.h"

GameSystem::GameSystem()
{
	GameInstance::createSingleton();
	GameInstance::sGetInstance()->onInit();

	GameLevelManager::sGetInstance()->createSingleton();
}

GameSystem::~GameSystem()
{
}

void GameSystem::onInit()
{
	DisplayManager::sGetInstance()->createSingleton();
	new GameLevelTest();
	new Level01();
	new Level02();
	new Level03();
	GameLevelManager::sGetInstance()->setDefaultLevel(1);
	
	CameraShake::sGetInstance()->createSingleton();
}

void GameSystem::onUpdate(float deltaTime)
{
	GameLevelManager::sGetInstance()->onUpdadte(deltaTime);
	//SceneManager::sGetInstance ()->onUpdate(deltaTime);
}
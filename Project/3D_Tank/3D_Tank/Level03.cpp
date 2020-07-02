#include "Level03.h"
#include "AITank.h"
#include "GameModeTP.h"
#include "RenderManager.h"

Level03::Level03()
{
	GameLevelManager::sGetInstance()->addLevel(3, this);
}

Level03::~Level03()
{
}

void Level03::enterLevel()
{
	mCurrentGameMode = new GameModeBase();
	mCurrentGameMode->onInit();

	SceneManager::sGetInstance()->setSkyBox(L"Skybox/Night");
	SceneManager::sGetInstance()->createSphere();
	mCanStart = true;
}

GameLevelBase * Level03::onUpdate(float deltaTime)
{
	SceneManager::sGetInstance()->onUpdate(deltaTime);

	if (DInputPC::getInstance().iskey(DIK_I))
	{
		RenderManager::sGetInstance()->rotateLight(deltaTime*100.0f, 0.0f, 0.0f);
	}
	if (DInputPC::getInstance().iskey(DIK_K))
	{
		RenderManager::sGetInstance()->rotateLight(deltaTime*-100.0f, 0.0f, 0.0f);
	}
	if (DInputPC::getInstance().iskey(DIK_J))
	{
		RenderManager::sGetInstance()->rotateLight(0.0f, deltaTime*100.0f, 0.0f);
	}
	if (DInputPC::getInstance().iskey(DIK_L))
	{
		RenderManager::sGetInstance()->rotateLight(0.0f, deltaTime*-100.0f, 0.0f);
	}

	SceneManager::sGetInstance()->onLateUpdate(deltaTime);

	return this;
}

void Level03::leaveLevel()
{
	Engine::sGetInstance()->enableGameMode(false);

}

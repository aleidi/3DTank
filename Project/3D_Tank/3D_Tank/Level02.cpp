#include "Level02.h"
#include "AITank.h"
#include "GameModeTP.h"
#include "RenderManager.h"
#include "GameInstance.h"
#include "PlayerController.h"

Level02::Level02()
{
	GameLevelManager::sGetInstance()->addLevel(2, this);
}

Level02::~Level02()
{
}

void Level02::enterLevel()
{

	mMap = SceneManager::sGetInstance()->createEmptyObject();
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/TownStreet", L"Objects/Wall");
	mMap->getTransform()->setScale(0.1f, 0.1f, 0.1f);

	SceneManager::sGetInstance()->setSkyBox(L"Skybox/Sand");

	//mCurrentGameMode = new GameModeBase();
	//mCurrentGameMode->onInit();
	mCurrentGameMode = new GameModeTP();

	mCanStart = true;
	new AITank(0);
	//Engine::sGetInstance()->enableGameMode(true);
	GameInstance::sGetInstance()->getPlayerController()->setEnable(true);
}

GameLevelBase * Level02::onUpdate(float deltaTime)
{
	if (!mCanStart)
	{
		return this;
	}

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

void Level02::leaveLevel()
{
	Engine::sGetInstance()->enableGameMode(false);

}

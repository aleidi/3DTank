#include "Level03.h"
#include "AITank.h"
#include "GameModeTP.h"
#include "RenderManager.h"
#include "DefaultPlayer.h"
#include "ShellContainer.h"

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
	ShellContainer::onInit();
	mCanStart = true;

	//Engine::sGetInstance()->enableGameMode(true);
}

GameLevelBase * Level03::onUpdate(float deltaTime)
{
	if (Camera::MainCamera == nullptr)
	{
		auto defaultPlayer = reinterpret_cast<DefaultPlayer*>(GameInstance::sGetInstance()->getPlayer());
		if (defaultPlayer != nullptr)
		{
			Camera::MainCamera = defaultPlayer->GetCamera();
		}
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

	//if (DInputPC::getInstance().iskeyDown(DIK_F6))
	//{
	//	Engine::sGetInstance()->startGame();
	//}
	return this;
}

void Level03::leaveLevel()
{
	Engine::sGetInstance()->enableGameMode(false);

}

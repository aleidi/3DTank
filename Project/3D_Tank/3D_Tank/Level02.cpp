#include "Level02.h"
#include "AITank.h"
#include "GameModeTP.h"
#include "RenderManager.h"
#include "EntityNames.h"

#include "GameInstance.h"
#include "Transform.h"
#include "GameCharacter.h"
AITank* enemy_01;
AITank* enemy_02;
AITank* enemy_boss;

Level02::Level02()
{
	GameLevelManager::sGetInstance()->addLevel(2, this);
}

Level02::~Level02()
{
}

void Level02::enterLevel()
{
	mCurrentGameMode = new GameModeBase();
	mCurrentGameMode->onInit();
	//mCurrentGameMode = new GameModeTP();

	mMap = SceneManager::sGetInstance()->createEmptyObject();
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/TownStreet", L"Objects/Wall");
	mMap->getTransform()->setScale(0.1f, 0.1f, 0.1f);

	enemy_boss = new AITank(ent_Tank_SuperEnemy);

	enemy_01 = new AITank(ent_Tank_Enemy01, ent_Tank_SuperEnemy);
	enemy_02 = new AITank(ent_Tank_Enemy02, ent_Tank_SuperEnemy);

	enemy_boss->changeTarget(ent_Tank_Enemy01);

	mCanStart = true;
}

GameLevelBase * Level02::onUpdate(float deltaTime)
{
	SceneManager::sGetInstance()->onUpdate(deltaTime);

	std::wstring wstr;
	float x = GameInstance::sGetInstance()->getPlayer()->getTransform()->getPosition().x;
	float z = GameInstance::sGetInstance()->getPlayer()->getTransform()->getPosition().z;
	wstr += std::to_wstring(x) + L"," + std::to_wstring(z);;
	Engine::sGetInstance()->showtText(wstr.c_str(),0,0,300,300,true);


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

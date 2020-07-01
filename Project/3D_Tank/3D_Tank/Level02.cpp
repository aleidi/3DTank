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
AITank* enemy_03;
AITank* enemy_04;
AITank* enemy_05;
AITank* enemy_06;
AITank* enemy_07;
AITank* enemy_08;
AITank* enemy_09;
AITank* enemy_10;
AITank* enemy_boss;
AITank* fakeplayer;

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

	fakeplayer = new AITank(ent_Tank_FakePlayer);

	enemy_boss = new AITank(ent_Tank_SuperEnemy, ent_Tank_FakePlayer);
	enemy_01 = new AITank(ent_Tank_Enemy01, ent_Tank_FakePlayer);
	enemy_02 = new AITank(ent_Tank_Enemy02, ent_Tank_FakePlayer);
	enemy_03 = new AITank(ent_Tank_Enemy03, ent_Tank_FakePlayer);
	enemy_04 = new AITank(ent_Tank_Enemy04, ent_Tank_FakePlayer);
	enemy_05 = new AITank(ent_Tank_Enemy05, ent_Tank_FakePlayer);
	enemy_06 = new AITank(ent_Tank_Enemy06, ent_Tank_FakePlayer);
	enemy_07 = new AITank(ent_Tank_Enemy07, ent_Tank_FakePlayer);
	enemy_08 = new AITank(ent_Tank_Enemy08, ent_Tank_FakePlayer);
	enemy_09 = new AITank(ent_Tank_Enemy09, ent_Tank_FakePlayer);
	enemy_10 = new AITank(ent_Tank_Enemy10, ent_Tank_FakePlayer);

	fakeplayer->changeTarget(ent_Tank_Enemy01);

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

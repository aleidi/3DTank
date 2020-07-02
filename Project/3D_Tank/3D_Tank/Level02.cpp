#include <thread>

#include "Level02.h"
#include "AITank.h"
#include "GameModeTP.h"
#include "RenderManager.h"
#include "GameInstance.h"
#include "PlayerController.h"
#include "EntityNames.h"
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
	SceneManager::sGetInstance()->setSkyBox(L"Skybox/Sand");


	std::thread t(&Level02::loadResourcce, this);
	t.detach();

}

GameLevelBase * Level02::onUpdate(float deltaTime)
{
	if (!mCanStart)
	{
		return this;
	}

	SceneManager::sGetInstance()->onUpdate(deltaTime);

	std::wstring wstr;
	float x = GameInstance::sGetInstance()->getPlayer()->getTransform()->getPosition().x;
	float z = GameInstance::sGetInstance()->getPlayer()->getTransform()->getPosition().z;
	wstr += std::to_wstring(x) + L"," + std::to_wstring(z);;
	Engine::sGetInstance()->showtText(wstr.c_str(), 0, 0, 300, 300, true);

	RenderManager::sGetInstance()->rotateLight(0.0f, deltaTime*10.0f, 0.0f);

	SceneManager::sGetInstance()->onLateUpdate(deltaTime);

	return this;
}

void Level02::leaveLevel()
{
	Engine::sGetInstance()->enableGameMode(false);

}

void Level02::loadResourcce()
{
	mMap = SceneManager::sGetInstance()->createEmptyObject();
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m0_wall3", L"Objects/Level/wall3");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m1_wall2", L"Objects/Level/wall2");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m2_wall5", L"Objects/Level/wall5");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m3_c2", L"Objects/Level/c2");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m4_c1", L"Objects/Level/c1");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m5_cn", L"Objects/Level/cn");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m6_P1", L"Objects/Level/P1");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m7_c4", L"Objects/Level/c4");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m8_arc1", L"Objects/Level/arc1");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m9_arc2", L"Objects/Level/arc2");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m10_arc3", L"Objects/Level/arc3");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m11_tree", L"Objects/Level/tree");
	SceneManager::sGetInstance()->createModel(*mMap, "Objects/Level/m12_reaf", L"Objects/Level/reaf");
	mMap->getTransform()->translate(0.0f, -0.075f, 0.0f);
	mMap->getTransform()->setScale(0.1f, 0.1f, 0.1f);
	mMap->getTransform()->setRotation(Vector3(0.0f,0.0f,0.001794f));

	//mCurrentGameMode = new GameModeBase();
	//mCurrentGameMode->onInit();
	mCurrentGameMode = new GameModeTP();

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

	GameInstance::sGetInstance()->getPlayerController()->setEnable(true);

	mCanStart = true;
}

#include <thread>

#include "Level02.h"
#include "AITank.h"
#include "PlayerTank.h"
#include "AIController.h"
#include "GameModeTP.h"
#include "RenderManager.h"
#include "GameInstance.h"
#include "PlayerController.h"
#include "EntityNames.h"
#include "Transform.h"
#include "GameCharacter.h"
#include "MessageDispatcher.h"
#include "AirWall.h"
#include "SM_construction_fence.h"
#include "SM_WaterTank.h"
#include "SM_Crate.h"
#include "FreightContainer_A.h"
#include "Potion.h"

/////////////////////////////////
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

Potion* potion1;

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
	float y = GameInstance::sGetInstance()->getPlayer()->getTransform()->getPosition().y;
	float z = GameInstance::sGetInstance()->getPlayer()->getTransform()->getPosition().z;
	wstr += std::to_wstring(x) + L"," + std::to_wstring(y) + L"," + std::to_wstring(z);
	Engine::sGetInstance()->showtText(wstr.c_str(), 0, 0, 300, 300, true);
	
	RenderManager::sGetInstance()->rotateLight(0.0f, deltaTime*10.0f, 0.0f);

	SceneManager::sGetInstance()->onLateUpdate(deltaTime);

	Dispatch->DispatchDelayedMessages();

	if (!secondloaded && isWaveClear(firstWaveAI) ) {
		loadSecondWave();
		wakeupWave(secondWaveAI);	
		secondloaded = true;
	}
	
	if (!thirdloaded && secondloaded && isWaveClear(secondWaveAI) ) {
		loadThirdWave();
		wakeupWave(thirdWaveAI);
		thirdloaded = true;
	}
	
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
	mMap->getTransform()->setScale(0.07f, 0.07f, 0.07f);

	//// seven buildings'

	Vector3 position, scale;
	position = Vector3(-16.5, 7, 12.5);
	scale = Vector3(21.5, 14, 16);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(-17, 7, -14.3);
	scale = Vector3(22, 14, 22.5);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(17, 6.8, -4.3);
	scale = Vector3(15.2, 13.7, 44.4);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(-16.5, 6.5, -40.6);
	scale = Vector3(21.2, 15, 15.3);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(17.4, 4.9, -40.6);
	scale = Vector3(15.3, 9.8, 14.2);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(-16.8, 7, -66.7);
	scale = Vector3(21.6, 14, 22.2);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(17.4, 6.5, -65.8);
	scale = Vector3(15.3, 13, 21.1);
	airWalls.push_back(new AirWall(position, scale));

	// four walls'
	position = Vector3(-1, 4.5, 32.2);
	scale = Vector3(75, 9, 0.05);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(-1, 4.5, -87.2);
	scale = Vector3(75, 9, 0.05);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(-37.8, 5.5, -28);
	scale = Vector3(0.05, 11.3, 120);
	airWalls.push_back(new AirWall(position, scale));

	position = Vector3(36.3, 5, -28);
	scale = Vector3(0.05, 10.3, 120);
	airWalls.push_back(new AirWall(position, scale));

	// ground's
	position = Vector3(-0.8, -0.57, -27.4);
	scale = Vector3(77.2, 1, 120);
	airWalls.push_back(new AirWall(position, scale));

	// obstacles fence
	position = Vector3(-38, -0.5, 33);
	scale = Vector3(0.05, 0.01, 0.01);
	Vector3 rotation = Vector3(0, -3.1425926 / 2.0, 0); // PI / 2
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-38, -0.5, 18);
	scale = Vector3(0.05, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-38, -0.5, 3);
	scale = Vector3(0.05, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-38, -0.5, -12);
	scale = Vector3(0.05, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-38, -0.5, -27);
	scale = Vector3(0.05, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-38, -0.5, -42);
	scale = Vector3(0.05, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-38, -0.5, -57);
	scale = Vector3(0.05, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-38, -0.5, -72);
	scale = Vector3(0.05, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-16, -0.5, 32.2);
	scale = Vector3(0.075, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-16, -0.5, -87);
	scale = Vector3(0.075, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-12.8, -0.5, 18.5);
	scale = Vector3(0.045, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-13, -0.5, 5.5);
	scale = Vector3(0.045, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-26.5, -0.5, 18.5);
	scale = Vector3(0.043, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-13.3, -0.5, -3.5);
	scale = Vector3(0.045, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-13.3, -0.5, -25);
	scale = Vector3(0.045, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-27, -0.5, -3.6);
	scale = Vector3(0.07, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-12.8, -0.5, -34.5);
	scale = Vector3(0.045, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-13, -0.5, -47.5);
	scale = Vector3(0.045, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-26.5, -0.5, -34.5);
	scale = Vector3(0.043, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-13.3, -0.5, -56);
	scale = Vector3(0.045, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-13.3, -0.5, -77.4);
	scale = Vector3(0.045, 0.01, 0.01);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-27, -0.5, -56);
	scale = Vector3(0.07, 0.01, 0.01);
	rotation = Vector3(0, -3.1425926 / 2.0, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));
	/////////////////////////////////////
	position = Vector3(1.0, 0, -26.0);
	scale = Vector3(0.02, 0.01, 0.03);
	rotation = Vector3(0, -3.1425926, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	position = Vector3(-6.0, 0, -19.0);
	scale = Vector3(0.02, 0.01, 0.03);
	rotation = Vector3(0, -3.1425926, 0);
	obstacles.push_back(new SM_construction_fence(position, rotation, scale));

	// obstacles FreightContainer
	position = Vector3(-19, 0, -50);
	scale = Vector3(0.03, 0.005, 0.005);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new FreightContainer_A(position, rotation, scale, 1));

	position = Vector3(30.5, 0, -4.0);
	scale = Vector3(0.018, 0.018, 0.018);
	rotation = Vector3(0, 25.0, 0);
	obstacles.push_back(new FreightContainer_A(position, rotation, scale, 1));

	// obstacles WaterTank
	position = Vector3(7, 0, -26.0);
	scale = Vector3(0.02, 0.02, 0.02);
	rotation = Vector3(0, 0, 0);
	obstacles.push_back(new SM_WaterTank(position, rotation, scale));

	////////////////////////////////////////////////////////////////
	//mCurrentGameMode = new GameModeBase();
	//mCurrentGameMode->onInit();
	mCurrentGameMode = new GameModeTP();

	loadFirstWave();
	wakeupWave(firstWaveAI);

	GameInstance::sGetInstance()->getPlayerController()->setEnable(true);
	reinterpret_cast<PlayerTank*>(GameInstance::sGetInstance()->getPlayer())->translate(30.0,0,9.0);

	// potion
	potion1 = new Potion();
	potion1->getTransform()->setPosition(Vector3(30.0, 0.0, 2.0));

	mCanStart = true;
}

void Level02::wakeupAI(int ID) {
	if (SceneManager::sGetInstance()->getAIController(ID) != nullptr ) 
		SceneManager::sGetInstance()->getAIController(ID)->wakeup();

}

void Level02::loadFirstWave() {
	firstWaveAI.push_back(new AITank(ent_Tank_Enemy01)); //ok
	firstWaveAI.push_back(new AITank(ent_Tank_Enemy02)); //ok
	firstWaveAI.push_back(new AITank(ent_Tank_Enemy03)); //ok
	//firstWaveAI.push_back(new AITank(ent_Tank_Enemy04)); //ok
	//firstWaveAI.push_back(new AITank(ent_Tank_Enemy05)); //ok
	//firstWaveAI.push_back(new AITank(ent_Tank_Enemy06)); //ok
	//firstWaveAI.push_back(new AITank(ent_Tank_Enemy07)); //ok
	//firstWaveAI.push_back(new AITank(ent_Tank_Enemy08)); //ok
	//firstWaveAI.push_back(new AITank(ent_Tank_Enemy09)); //ok
	//firstWaveAI.push_back(new AITank(ent_Tank_Enemy10)); //ok	
}

void Level02::loadSecondWave() {
	for (int i = 0; i < firstWaveAI.size(); ++i) {
		firstWaveAI[i]->destroy();
	}

	secondWaveAI.push_back(new AITank(ent_Tank_Enemy04));
	secondWaveAI.push_back(new AITank(ent_Tank_Enemy05));
	secondWaveAI.push_back(new AITank(ent_Tank_Enemy06));
	secondWaveAI.push_back(new AITank(ent_Tank_Enemy07));
}

void Level02::loadThirdWave() {
	for (int i = 0; i < secondWaveAI.size(); ++i) {
		secondWaveAI[i]->destroy();
	}
	thirdWaveAI.push_back(new AITank(ent_Tank_Enemy08));
	thirdWaveAI.push_back(new AITank(ent_Tank_Enemy09));
	thirdWaveAI.push_back(new AITank(ent_Tank_Enemy10));
	thirdWaveAI.push_back(new AITank(ent_Tank_SuperEnemy));
}

bool Level02::isWaveClear(std::vector<AITank*> thisWave) {
	for (int i = 0; i < thisWave.size(); ++i) {
		if (thisWave[i]->isAlive())
			return false;
	}

	return true;
}

void Level02::wakeupWave(std::vector<AITank*> thisWave) {
	for (int i = 0; i < thisWave.size(); ++i) {
		wakeupAI(thisWave[i]->getID());
	}

}
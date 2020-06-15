#include "GameLevelTest.h"
#include "GameCommon.h"
#include "GameModeBase.h"

#include "TankGamePlay.h"
#include "TankBatteryCtrl.h"
#include "RenderManager.h"
#include "EnemyTank.h"
#include "EntityNames.h"
#include "AIController.h"


GameObject* hq;
GameObject* tankBattery;
GameObject* tankBody;
GameObject* tankTrackL;
GameObject* tankTrackR;
GameObject* cam;
GameObject* follow;
EnemyTank* enemy;
AIController* aiController;

GameLevelTest::GameLevelTest()
{
	GameLevelManager::sGetInstance()->addLevel(0, this);
}

GameLevelTest::~GameLevelTest()
{
}

void GameLevelTest::enterLevel()
{
	mCurrentGameMode = new GameModeBase();
	mCurrentGameMode->onInit();

	GameObject* cube = SceneManager::sGetInstance()->createCube();

	//hq = SceneManager::sGetInstance()->createEmptyObject();
	//hq->setName("hq");
	//ScriptComponent* sc = new TankGamePlay(hq);
	//hq->addScriptComponent(sc);

	//follow = SceneManager::sGetInstance()->createEmptyObject();
	//follow->setName("follow");
	//follow->attach(*hq);
	//follow->getTransform()->translate(0.0f, 20.0f, -40.0f);

	////cam = SceneManager::sGetInstance()->createEmptyObject();
	////cam->setName("camera");
	////Camera* maincam = new Camera(cam);
	////cam->addComponent(maincam);
	////maincam->MainCamera = maincam;
	////cam->addComponent(new CameraCtrl(cam));
	////cam->getTransform()->rotateX(20);

	//tankBattery = SceneManager::sGetInstance()->createEmptyObject();
	//tankBattery->setName("tankBattery");
	//SceneManager::sGetInstance()->createModel(*tankBattery, "Tank\\TankBattery", L"Tank\\TankTex");
	//tankBattery->attach(*hq);
	//ScriptComponent* sc2 = new TankBatteryCtrl(tankBattery);
	//tankBattery->addScriptComponent(sc2);

	//tankBody = SceneManager::sGetInstance()->createEmptyObject();
	//tankBody->setName("tankBody");
	//SceneManager::sGetInstance()->createModel(*tankBody, "Tank\\TankBody", L"Tank\\TankTex");
	//tankBody->attach(*hq);

	//tankTrackL = SceneManager::sGetInstance()->createEmptyObject();
	//tankTrackL->setName("tankTrackL");
	//SceneManager::sGetInstance()->createModel(*tankTrackL, "Tank\\TankTrack_L", L"Tank\\TankTrack");
	//tankTrackL->attach(*hq);

	//tankTrackR = SceneManager::sGetInstance()->createEmptyObject();
	//tankTrackR->setName("tankTrackR");
	//SceneManager::sGetInstance()->createModel(*tankTrackR, "Tank\\TankTrack_R", L"Tank\\TankTrack");
	//tankTrackR->attach(*hq);

	//GameObject* ground = SceneManager::sGetInstance()->createEmptyObject();
	//ground->setName("Ground");
	//SceneManager::sGetInstance()->createModel(*ground, "Objects\\SM_ZPlane_01a", L"Objects\\TX_RockyMud_01_ALB");
	//ground->getTransform()->rotateZ(180);

	//GameObject* freightContainer_A = SceneManager::sGetInstance()->createEmptyObject();
	//freightContainer_A->setName("freightContainer_A");
	//SceneManager::sGetInstance()->createModel(*freightContainer_A, "Objects\\SM_FreightContainer_01", L"Objects\\TX_FreightContainer_01a_ALB");
	//freightContainer_A->getTransform()->translate(Vector3::right*20.0f);
	//freightContainer_A->getTransform()->setScale(Vector3(0.025f, 0.025f, 0.025f));

	//GameObject* freightContainer_B = SceneManager::sGetInstance()->createEmptyObject();
	//freightContainer_B->setName("freightContainer_B");
	//SceneManager::sGetInstance()->createModel(*freightContainer_B, "Objects\\SM_FreightContainer_01", L"Objects\\TX_FreightContainer_01b_ALB");
	//freightContainer_B->getTransform()->translate(Vector3::right*-15.0f + Vector3::forward*20.0f);
	//freightContainer_B->getTransform()->setScale(Vector3(0.03f, 0.03f, 0.03f));

	//GameObject* SM_WaterTank = SceneManager::sGetInstance()->createEmptyObject();
	//SM_WaterTank->setName("SM_WaterTank");
	//SceneManager::sGetInstance()->createModel(*SM_WaterTank, "Objects\\SM_WaterTank_01a", L"Objects\\TX_PortableWaterTank_01_ALB");
	//SM_WaterTank->getTransform()->translate(Vector3::right*-30.0f + Vector3::forward*50.0f);
	//SM_WaterTank->getTransform()->setScale(Vector3(0.1f, 0.1f, 0.1f));

	//GameObject* SM_Crate = SceneManager::sGetInstance()->createEmptyObject();
	//SM_Crate->setName("SM_Crate");
	//SceneManager::sGetInstance()->createModel(*SM_Crate, "Objects\\SM_Crate_01a", L"Objects\\TX_Crates_01a_ALB");
	//SM_Crate->getTransform()->translate(Vector3::forward*50.0f);
	//SM_Crate->getTransform()->setScale(Vector3(0.1f, 0.1f, 0.1f));

	//GameObject* SM_construction_fence = SceneManager::sGetInstance()->createEmptyObject();
	//SM_construction_fence->setName("SM_construction_fence");
	//SceneManager::sGetInstance()->createModel(*SM_construction_fence, "Objects\\SM_construction_fence_01a", L"Objects\\TX_ConstructionFence_01a_ALB");
	//SM_construction_fence->getTransform()->translate(Vector3::right*50.0f + Vector3::forward*50.0f);
	//SM_construction_fence->getTransform()->setScale(Vector3(0.1f, 0.1f, 0.1f));

	//hq->getTransform()->setScale(Vector3(0.1f, 0.1f, 0.1f));


	//set ai
	enemy = new EnemyTank(ent_Tank_Enemy);
	cube->attach(*enemy);
	aiController = new AIController();
	aiController->posses(enemy);
}

GameLevelBase* GameLevelTest::onUpdate(float deltaTime)
{
	SceneManager::sGetInstance()->onUpdate(deltaTime);

	if (DInputPC::getInstance().iskeyDown(DIK_F1))
	{
		return GameLevelManager::sGetInstance()->changeLevel(1);
	}

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
	return this;
}

void GameLevelTest::leaveLevel()
{
	delete mCurrentGameMode;
	mCurrentGameMode = nullptr;
}

#include "GameLevelTest.h"
#include "GameCommon.h"
#include "GameModeBase.h"

#include "TankGamePlay.h"
#include "TankBatteryCtrl.h"
#include "RenderManager.h"
#include "EnemyTank.h"
#include "EntityManager.h"
#include "EntityNames.h"
#include "MessageDispatcher.h"
#include "AIController.h"
#include "MessageTypes.h"
#include "ShellFlyComponent.h"
#include "CollisionManager.h"
#include "BoundingSphere.h"
#include "BoundingCube.h"
#include "SoundComponent.h"
#include "SoundManager.h"
#include "Shell.h"
#include <windows.h>

GameObject* hq;
GameObject* tankBattery;
GameObject* tankBody;
GameObject* tankTrackL;
GameObject* tankTrackR;
GameObject* cam;
GameObject* follow;
GameObject* SM_WaterTank;
GameObject* SM_Crate;
GameObject* shell;
GameObject* collider;
SoundComponent* sound;
EnemyTank* enemy;
EnemyTank* enemytarget;
EnemyTank* enemy1;
EnemyTank* enemy2;
EnemyTank* enemy3;
EnemyTank* enemy4;
EnemyTank* enemy5;
AIController* aiController;
AIController* aiControllertarget;
AIController* aiController1;
AIController* aiController2;
AIController* aiController3;
AIController* aiController4;
AIController* aiController5;

bool tankFire = false;

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
	SceneManager::sGetInstance()->createCube()->getTransform()->setPosition(Vector3::right * 1.0f);

	SoundManager::sGetInstance()->onInit();

	CollisionManager::sGetInstance()->onInit();

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

	DirectX::XMVECTOR maxPoint, minPoint;
	SM_WaterTank = SceneManager::sGetInstance()->createEmptyObject();
	SM_WaterTank->setName("SM_WaterTank");
	SceneManager::sGetInstance()->createModel(*SM_WaterTank, "Objects\\SM_WaterTank_01a", L"Objects\\TX_PortableWaterTank_01_ALB",maxPoint,minPoint);
	SM_WaterTank->getTransform()->translate(Vector3::forward*20.0f + Vector3::up*-10.f + Vector3::right*-5.f);
	SM_WaterTank->getTransform()->setScale(Vector3(0.1f, 0.1f, 0.1f));
	/*BoundingCube* SM_WaterTank_BoundingCube = new BoundingCube(SM_WaterTank);
	SM_WaterTank_BoundingCube->createBoundingCube(maxPoint, minPoint,0);
	SM_WaterTank->addComponent(SM_WaterTank_BoundingCube);
	DirectX::BoundingOrientedBox out;
	SM_WaterTank->getTransform()->calcultateTransformMatrix();
	SM_WaterTank_BoundingCube->box.Transform(out, SM_WaterTank->getTransform()->getLocalToWorldMatrix());
	SM_WaterTank_BoundingCube->box = out;
	SM_WaterTank->cube = SM_WaterTank_BoundingCube;*/

	SM_Crate = SceneManager::sGetInstance()->createEmptyObject();
	SM_Crate->setName("SM_Crate");
	SceneManager::sGetInstance()->createModel(*SM_Crate, "Objects\\SM_Crate_01a", L"Objects\\TX_Crates_01a_ALB", maxPoint, minPoint);
	SM_Crate->getTransform()->translate(Vector3::right*50.0f + Vector3::forward*50.f);
	SM_Crate->getTransform()->setScale(Vector3(0.1f, 0.1f, 0.1f));
	SM_Crate->getTransform()->calcultateTransformMatrix();
	BoundingCube* SM_Crate_BoundingCube = new BoundingCube(SM_Crate);
	SM_Crate_BoundingCube->createBoundingCube(maxPoint, minPoint, 0);
	SM_Crate->addComponent(SM_Crate_BoundingCube);
	SM_Crate_BoundingCube->box.Transform(SM_Crate_BoundingCube->box, SM_Crate->getTransform()->getLocalToWorldMatrix());
	SM_Crate->cube = SM_Crate_BoundingCube;

	//GameObject* SM_construction_fence = SceneManager::sGetInstance()->createEmptyObject();
	//SM_construction_fence->setName("SM_construction_fence");
	//SceneManager::sGetInstance()->createModel(*SM_construction_fence, "Objects\\SM_construction_fence_01a", L"Objects\\TX_ConstructionFence_01a_ALB");
	//SM_construction_fence->getTransform()->translate(Vector3::right*50.0f + Vector3::forward*50.0f);
	//SM_construction_fence->getTransform()->setScale(Vector3(0.1f, 0.1f, 0.1f));

	//hq->getTransform()->setScale(Vector3(0.1f, 0.1f, 0.1f));
	//set ai
	
	enemy = new EnemyTank(ent_Tank_Enemy);
	EntityMgr->registerEntity(enemy);
	enemy->setMaxSpeed(1.5f);
	aiController = SceneManager::sGetInstance()->createAIController(ent_Tank_Enemy);
	aiController->posses(enemy);
	enemytarget = new EnemyTank(ent_Tank_SuperEnemy);
	enemytarget->getTransform()->setPosition(Vector3(10, 0, 10));
	EntityMgr->registerEntity(enemytarget);
	aiControllertarget = SceneManager::sGetInstance()->createAIController(ent_Tank_SuperEnemy);
	aiControllertarget->getFSM()->setCurrentState(Wander::getInstance());
	aiControllertarget->posses(enemytarget);

	aiController->setTarget(enemytarget);
	aiControllertarget->setTarget(enemy);
	//SoundManager::sGetInstance()->playSound(3);
	//shell = SceneManager::sGetInstance()->createSphere();
	//shell->getTransform()->Forward = enemy->getTransform()->Forward;
	//shell->getTransform()->setPosition(enemy->getTransform()->getPosition() + enemy->getTransform()->Forward*0.6f + enemy->getTransform()->Up*0.18f + enemy->getTransform()->Right*0.04f);
	//shell->getTransform()->setScale(Vector3(0.02f, 0.02f, 0.02f));
	//SceneManager::sGetInstance()->addGameObjectToPool(shell);
	//ShellFlyComponent* shellFly = new ShellFlyComponent(shell);
	//shell->addComponent(shellFly);
	//MBoundingSphere* shellBoundingSphere = new MBoundingSphere(shell);
	//shellBoundingSphere->createBoundingSphere(shell->getTransform()->getPosition(), 0.1, 1);
	//shell->addComponent(shellBoundingSphere);
	//shell->sphere = shellBoundingSphere;

	SoundManager::sGetInstance()->setLisenterPosition(enemy->getTransform()->getPosition());
}

GameLevelBase* GameLevelTest::onUpdate(float deltaTime)
{
	if (DInputPC::getInstance().iskeyDown(DIK_F)){
		Shell* sh = new Shell(enemy->getTransform()->getPosition() + enemy->getTransform()->Forward*0.6f + enemy->getTransform()->Up*0.18f + enemy->getTransform()->Right*0.04f, enemy->getTransform()->Forward, 0);

		shell = SceneManager::sGetInstance()->createSphere();
		shell->getTransform()->Forward = SM_WaterTank->getTransform()->Forward * -1;
		shell->getTransform()->setPosition(SM_WaterTank->getTransform()->getPosition() + SM_WaterTank->getTransform()->Forward*0.6f + enemy->getTransform()->Up*0.18f+enemy->getTransform()->Right*0.04f);
		shell->getTransform()->setScale(Vector3(0.02f, 0.02f, 0.02f));
		SceneManager::sGetInstance()->addGameObjectToPool(shell);
		ShellFlyComponent* shellFly = new ShellFlyComponent(shell);
		shell->addComponent(shellFly);
		MBoundingSphere* shellBoundingSphere = new MBoundingSphere(shell);
		shellBoundingSphere->createBoundingSphere(shell->getTransform()->getPosition(), 0.1f, 1);
		shell->addComponent(shellBoundingSphere);
		shell->sphere = shellBoundingSphere;
		shellFly->setTarget(enemy);
		tankFire = true;
		sound = new SoundComponent(shell);
		sound->setPosition();
		shell->addComponent(sound);
		SoundManager::sGetInstance()->playSound(sound->mChannel, 0);
	}
	if (shell) {
		//SoundManager::sGetInstance()->setSoundPosAndVel(shell->getTransform()->getPosition()*0.5, shell->getTransform()->Forward, 0);
		SoundManager::sGetInstance()->onUpdate();
	}

 	if (tankFire == true && shell != NULL && CollisionManager::sGetInstance()->collisionCheck_SphereToCube(shell->sphere, &collider) == true) {
		SoundManager::sGetInstance()->stop(sound->mChannel);
		tankFire = false;
		SoundManager::sGetInstance()->playSound(sound->mChannel,6);
	}

	////////////////put in bullet class int the future /////////////////
	if (DInputPC::getInstance().iskeyDown(DIK_O))
	{
		Dispatch->Dispatch_Message(0,
			reinterpret_cast<EnemyTank*>(aiController->getPawn())->getID(),
			reinterpret_cast<EnemyTank*>(aiController->getPawn())->getID(),
			Msg_IsAttacked,
			NO_ADDITIONAL_INFO);
	}

	Dispatch->DispatchDelayedMessages();
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

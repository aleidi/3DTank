#include <sstream>

#include "Engine.h"
#include "Window.h"
#include "SceneManager.h"
#include "ComponentFactory.h"
#include "Configuration.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//test
#include "GameObject.h"
#include "Transform.h"
#include "ModelMesh.h"
#include "TankGamePlay.h"
#include "TankBatteryCtrl.h"
#include "Camera.h"
#include "CameraCtrl.h"
#include "Collision.h"

Engine* Engine::sInstance = nullptr;

//test code
GameObject* hq;
GameObject* tankBattery;
GameObject* tankBody;
GameObject* tankTrackL;
GameObject* tankTrackR;
GameObject* cam;
GameObject* follow;

Collision* collision;

static float dis = 0.0f;

Engine::Engine(Window& wnd)
	:
	mWnd(wnd),
	mSound(std::make_unique<Sound>()),
	mRendering(std::make_unique<Rendering>(wnd)),
	mGameSystem(std::make_unique<GameSystem>()),
	mIsGameMode(false)
{
	onPreInit();

	onInit();
}

Engine * Engine::sGetInstance()
{
	return sInstance;
}

void Engine::createSingleton(Window & wnd)
{
	assert(!sInstance);
	sInstance = new Engine(wnd);
}

void Engine::Destroy()
{
	delete sInstance;
	sInstance = nullptr;
}

void Engine::onPreInit()
{
	//Timer Init
	mTimer.reset();

	//SceneManagerInit
	SceneManager::createSingleton();

	//Rendering Init
	mRendering.get()->onInit();

	//eui creation
	mEui = std::make_unique<ImGuiFrame>(
		mWnd.getHwnd(), mRendering->getGFX()->GetDevice(), mRendering->getGFX()->GetContext());
}

void Engine::onInit()
{
	//Input Init
	DInputPC::getInstance().onInit(mWnd.getHwnd(), mWnd.getHinst(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );

	//Sound Init
	mSound->onInit();

	//ImGui Init


	//EUI Init
	mEui->onInit();

	//Game Init

#pragma region TestCode

	//test code
	 fScale = 1.0f;
	 fTrans_x = 0.0f;
	 fTrans_y = 0.0f;
	 fTrans_z = 0.0f;
	 fRot_x = 0.0f;
	 fRot_y = 0.0f;
	 fRot_z = 0.0f;
	 fspeed = 300.0f;
	 rspeed = 5.0f;

	hq = SceneManager::sGetInstance()->createEmptyObject();
	hq->setName("hq");
	ScriptComponent* sc = new TankGamePlay(hq);
	hq->addScriptComponent(sc);
	
	follow = SceneManager::sGetInstance()->createEmptyObject();
	follow->setName("follow");
	follow->attach(*hq);
	follow->getTransform()->translate(0.0f, 20.0f, -40.0f);

	cam = SceneManager::sGetInstance()->createEmptyObject();
	cam->setName("camera");
	Camera* maincam = new Camera(cam);
	cam->addComponent(maincam);
	maincam->MainCamera = maincam;
	cam->addComponent(new CameraCtrl(cam));
	cam->getTransform()->rotateX(20);

	tankBattery = SceneManager::sGetInstance()->createEmptyObject();
	tankBattery->setName("tankBattery");
	SceneManager::sGetInstance()->createModel(*tankBattery, "Tank\\TankBattery", L"Tank\\TankTex");
	tankBattery->attach(*hq);
	ScriptComponent* sc2 = new TankBatteryCtrl(tankBattery);
	tankBattery->addScriptComponent(sc2);

	tankBody = SceneManager::sGetInstance()->createEmptyObject();
	tankBody->setName("tankBody");
	SceneManager::sGetInstance()->createModel(*tankBody, "Tank\\TankBody", L"Tank\\TankTex");
	tankBody->attach(*hq);

	tankTrackL = SceneManager::sGetInstance()->createEmptyObject();
	tankTrackL->setName("tankTrackL");
	SceneManager::sGetInstance()->createModel(*tankTrackL, "Tank\\TankTrack_L", L"Tank\\TankTrack");
	tankTrackL->attach(*hq);

	tankTrackR = SceneManager::sGetInstance()->createEmptyObject();
	tankTrackR->setName("tankTrackR");
	SceneManager::sGetInstance()->createModel(*tankTrackR, "Tank\\TankTrack_R", L"Tank\\TankTrack");
	tankTrackR->attach(*hq);

	GameObject* ground = SceneManager::sGetInstance()->createEmptyObject();
	ground->setName("Ground");
	SceneManager::sGetInstance()->createModel(*ground, "Objects\\SM_ZPlane_01a", L"Objects\\TX_RockyMud_01_ALB");

	GameObject* freightContainer_A = SceneManager::sGetInstance()->createEmptyObject();
	freightContainer_A->setName("freightContainer_A");
	SceneManager::sGetInstance()->createModel(*freightContainer_A, "Objects\\SM_FreightContainer_01", L"Objects\\TX_FreightContainer_01a_ALB");
	freightContainer_A->getTransform()->translate(Vector3::right*20.0f);
	freightContainer_A->getTransform()->setScale(Vector3(0.025f, 0.025f, 0.025f));

	GameObject* freightContainer_B = SceneManager::sGetInstance()->createEmptyObject();
	freightContainer_B->setName("freightContainer_B");
	SceneManager::sGetInstance()->createModel(*freightContainer_B, "Objects\\SM_FreightContainer_01", L"Objects\\TX_FreightContainer_01b_ALB");
	freightContainer_B->getTransform()->translate(Vector3::right*-15.0f + Vector3::forward*20.0f);
	freightContainer_B->getTransform()->setScale(Vector3(0.03f, 0.03f, 0.03f));

	GameObject* SM_WaterTank = SceneManager::sGetInstance()->createEmptyObject();
	SM_WaterTank->setName("SM_WaterTank");
	SceneManager::sGetInstance()->createModel(*SM_WaterTank, "Objects\\SM_WaterTank_01a", L"Objects\\TX_PortableWaterTank_01_ALB");
	SM_WaterTank->getTransform()->translate(Vector3::right*-30.0f + Vector3::forward*50.0f);
	SM_WaterTank->getTransform()->setScale(Vector3(0.1f, 0.1f, 0.1f));

	GameObject* SM_Crate = SceneManager::sGetInstance()->createEmptyObject();
	SM_Crate->setName("SM_Crate");
	SceneManager::sGetInstance()->createModel(*SM_Crate, "Objects\\SM_Crate_01a", L"Objects\\TX_Crates_01a_ALB");
	SM_Crate->getTransform()->translate(Vector3::forward*50.0f);
	SM_Crate->getTransform()->setScale(Vector3(0.1f, 0.1f, 0.1f));

	GameObject* SM_construction_fence = SceneManager::sGetInstance()->createEmptyObject();
	SM_construction_fence->setName("SM_construction_fence");
	SceneManager::sGetInstance()->createModel(*SM_construction_fence, "Objects\\SM_construction_fence_01a", L"Objects\\TX_ConstructionFence_01a_ALB");
	SM_construction_fence->getTransform()->translate(Vector3::right*50.0f + Vector3::forward*50.0f);
	SM_construction_fence->getTransform()->setScale(Vector3(0.1f, 0.1f, 0.1f));

	GameObject* obstacle = SceneManager::sGetInstance()->createSphere();
	obstacle->setName("obstacle");
	Vector3 pos(20.f, 5.f, 5.f);
	Vector3 scale(3.f, 3.f, 3.f);
	obstacle->getTransform()->setPosition(pos);
	obstacle->getTransform()->setScale(scale);
	collision = new Collision();
	float radius = 5.f;
	collision->createSphere(obstacle->getTransform()->getLocalPosition(),radius);
	Vector3 extents(10.f, 10.f, 10.f);
	collision->createCube(hq->getTransform()->getPosition(), extents);

	hq->getTransform()->setScale(Vector3(0.1f, 0.1f, 0.1f));
	hq->setLastFramePosition(hq->getTransform()->getPosition());

#pragma endregion

	
}

void Engine::run()
{
	//Timer update
	mTimer.tick();
	float deltaTime = mTimer.getDeltaTIme();
	calculateFrameStats();

	//Input Update
	DInputPC::getInstance().onUpdate();

	//Physics Update
	SceneManager::sGetInstance()->onEngineFixedUpdate(FixedDeltaTime);

	//Game Update

	SceneManager::sGetInstance()->onEngineUpdate(deltaTime);

	if (mIsGameMode)
	{
		mGameSystem->onUpdate(deltaTime);
		mSound->playBGM();
	}
	collision->transformCube(collision->mCube[0], hq->getTransform()->getPosition());
	bool isCollision = collision->cubeCollisionSphere(collision->mCube[0], collision->mSphere[0]);
	if (isCollision) {
		mSound->setPause(MusicIndex(BGM));
		hq->setLastFramePosition(hq->getLastFramePosition());
		hq->getTransform()->setPosition(hq->getLastFramePosition());
	}
	else {
		mSound->setReplay(MusicIndex(BGM));
		hq->setLastFramePosition(hq->getTransform()->getPosition());
	}

#pragma region test code

	if (DInputPC::getInstance().iskeyDown(DIK_SPACE))
	{
		mIsGameMode = true;
	}

#pragma endregion


	//Sound Update
	dis += fTrans_z;
	mSound->onUpdate(dis);

	//PreRender
	mRendering.get()->onPreRender(deltaTime);

	//OnRender
	mRendering.get()->onRender(deltaTime);

	//PostRender
	mRendering.get()->onPostRender(deltaTime);

	//gui update

	//eui update
	mEui->onUpdate(deltaTime);


	mRendering.get()->onEndRender(deltaTime);
}

void Engine::showtText(const std::wstring & str = L"", float leftTopX=0, float leftTopY=0, float width=0, float height=0, bool canShow = false)
{
	mRendering->getGFX()->setShowText(str, leftTopX, leftTopY, width, height, canShow);
}

void Engine::calculateFrameStats()
{
	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	++frameCnt;

	if ((mTimer.getTotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt;
		float mspf = 1000 / fps;

		std::wostringstream outs;
		outs.precision(6);
		outs << WNDTITLE << "   " << "FPS: " << fps << "   " << "Frame Time: " << mspf << "(ms)";
		SetWindowText(mWnd.getHwnd(), outs.str().c_str());
		
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}
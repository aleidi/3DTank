#include <sstream>
#include "Engine.h"
#include "Window.h"
#include "SceneManager.h"
#include "ComponentFactory.h"

#include "GameObject.h"
#include "Transform.h"
#include "ModelMesh.h"
#include "TankGamePlay.h"
#include "TankBatteryCtrl.h"
#include "Camera.h"

Engine* Engine::sInstance = nullptr;

//test code
GameObject* hq;
GameObject* tankBattery;
GameObject* tankBody;
GameObject* tankTrackL;
GameObject* tankTrackR;
GameObject* cam;
GameObject* follow;

static float dis = 0.0f;

Engine::Engine(Window& wnd)
	:
	mWnd(wnd),
	mSound(std::make_unique<Sound>()),
	mRendering(std::make_unique<Rendering>(wnd)),
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
}

void Engine::onInit()
{

	//test code
	calculateFrameStats();

	 fScale = 1.0f;
	 fTrans_x = 0.0f;
	 fTrans_y = 0.0f;
	 fTrans_z = 0.0f;
	 fRot_x = 0.0f;
	 fRot_y = 0.0f;
	 fRot_z = 0.0f;
	 fspeed = 300.0f;
	 rspeed = 5.0f;

	//Input Init
	DInputPC::getInstance().onInit(mWnd.getHwnd(), mWnd.getHinst(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );

	//Sound Init
	mSound->onInit();
	mSound->playBGM();

	//Gui Init

	//EUI Init

	//Game Init
	//SceneManager::sGetInstance()

	//test code
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
	cam->attach(*follow);
	cam->getTransform()->rotateX(20);

	tankBattery = SceneManager::sGetInstance()->createEmptyObject();
	tankBattery->setName("tankBattery");
	SceneManager::sGetInstance()->createModel(*tankBattery, "Tank\\TankBattery", L"Tank\\TankTex");
	tankBattery->attach(*hq);
	ScriptComponent* sc2 = new TankBatteryCtrl(tankBattery);
	tankBattery->addScriptComponent(sc2);

	GameObject* tankBody = SceneManager::sGetInstance()->createEmptyObject();
	tankBody->setName("tankBody");
	SceneManager::sGetInstance()->createModel(*tankBody, "Tank\\TankBody", L"Tank\\TankTex");
	tankBody->attach(*hq);

	GameObject* tankTrackL = SceneManager::sGetInstance()->createEmptyObject();
	tankTrackL->setName("tankTrackL");
	SceneManager::sGetInstance()->createModel(*tankTrackL, "Tank\\TankTrack_L", L"Tank\\TankTrack");
	tankTrackL->attach(*hq);

	GameObject* tankTrackR = SceneManager::sGetInstance()->createEmptyObject();
	tankTrackR->setName("tankTrackR");
	SceneManager::sGetInstance()->createModel(*tankTrackR, "Tank\\TankTrack_R", L"Tank\\TankTrack");
	tankTrackR->attach(*hq);

	hq->getTransform()->Scale = Vector3(0.1f, 0.1f, 0.1f);
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

	//Game Update
	SceneManager::sGetInstance()->onEngineUpdate(deltaTime);
	if (mIsGameMode)
	{
		SceneManager::sGetInstance()->onUpdate(deltaTime);
	}

	//Sound Update
	dis += fTrans_z;
	mSound->onUpdate(dis);

	//PreRender
	mRendering.get()->onPreRender(deltaTime);

	//OnRender
	mRendering.get()->onRender(deltaTime);

#pragma region test code
	float dt = mTimer.getDeltaTIme() * fspeed;
	float dt2 = mTimer.getDeltaTIme() * rspeed;
	//XMVECTOR v = mRendering.get()->getGFX()->getCamPos();
	//if (DInputPC::getInstance().iskey(DIK_W))
	//{
	//	v = mRendering.get()->getGFX()->getcamForward();
	//	v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
	//	v = XMVectorAdd(mRendering.get()->getGFX()->getCamPos(), v);
	//}
	//if (DInputPC::getInstance().iskey(DIK_S))
	//{
	//	v = mRendering.get()->getGFX()->getcamForward();
	//	v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
	//	v = XMVectorSubtract(mRendering.get()->getGFX()->getCamPos(),v);

	//}
	//if (DInputPC::getInstance().iskey(DIK_A))
	//{
	//	v = mRendering.get()->getGFX()->getcamRight();
	//	v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
	//	v = XMVectorSubtract(mRendering.get()->getGFX()->getCamPos(), v);
	//}
	//if (DInputPC::getInstance().iskey(DIK_D))
	//{
	//	v = mRendering.get()->getGFX()->getcamRight();
	//	v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
	//	v = XMVectorAdd(mRendering.get()->getGFX()->getCamPos(), v);
	//}
	//if (DInputPC::getInstance().iskey(DIK_Q))
	//{
	//	v = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	//	v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
	//	v = XMVectorAdd(mRendering.get()->getGFX()->getCamPos(), v);
	//}
	//if (DInputPC::getInstance().iskey(DIK_E))
	//{
	//	v = XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f);
	//	v = XMVectorMultiply(v, XMVectorSet(dt, dt, dt, dt));
	//	v = XMVectorAdd(mRendering.get()->getGFX()->getCamPos(), v);
	//}
	//if (DInputPC::getInstance().iskey(DIK_I))
	//{
	//	fRot_x -= mTimer.getDeltaTIme() * rspeed;
	//}
	//if (DInputPC::getInstance().iskey(DIK_K))
	//{
	//	fRot_x += mTimer.getDeltaTIme() * rspeed;
	//}
	//if (DInputPC::getInstance().iskey(DIK_J))
	//{
	//	fRot_y -= mTimer.getDeltaTIme() * rspeed;
	//}
	//if (DInputPC::getInstance().iskey(DIK_L))
	//{
	//	fRot_y += mTimer.getDeltaTIme() * rspeed;
	//}
	//if (DInputPC::getInstance().iskey(DIK_U))
	//{
	//	fRot_z -= mTimer.getDeltaTIme() * rspeed;
	//}
	//if (DInputPC::getInstance().iskey(DIK_O))
	//{
	//	fRot_z += mTimer.getDeltaTIme() * rspeed;
	//}
	//mRendering.get()->getGFX()->CamSetPosition(v);
	//mRendering.get()->getGFX()->CamSetRotation(fRot_x, fRot_y, fRot_z);


#pragma endregion

	if (DInputPC::getInstance().iskeyDown(DIK_SPACE))
	{
		mIsGameMode = true;
	}

	//PostRender
	mRendering.get()->onPostRender(deltaTime);

	/*
	gameUI.Update();
	eui.update();
	*/


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
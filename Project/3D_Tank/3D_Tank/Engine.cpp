#include <sstream>

#include "Engine.h"
#include "Window.h"
#include "SceneManager.h"
#include "ComponentFactory.h"
#include "Configuration.h"
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//test
#include "Rendering.h"
#include "Graphics.h"

#include "Collision.h"

Engine* Engine::sInstance = nullptr;

//test code
GameObject* bullet;

Collision* collision;

Vector3 bulletDirection;
bool fireBullet = false;

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
	mGameSystem->onInit();
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



	//GameObject* obstacle = SceneManager::sGetInstance()->createSphere();
	//obstacle->setName("obstacle");
	//Vector3 pos(20.f, 5.f, 5.f);
	//Vector3 scale(3.f, 3.f, 3.f);
	//obstacle->getTransform()->setPosition(pos);
	//obstacle->getTransform()->translate(Vector3::right*20.f + Vector3::forward*20.f + Vector3::up*5.f);
	//obstacle->getTransform()->setScale(scale);

	//collision = new Collision();
	//float radius = 5.f;
	//collision->createSphere(obstacle->getTransform()->getLocalPosition(),radius);
	//Vector3 extents(10.f, 10.f, 10.f);
	//collision->createCube(hq->getTransform()->getPosition(), extents);

	//hq->setLastFramePosition(hq->getTransform()->getPosition());

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
	//collision->transformCube(collision->mCube[0], hq->getTransform()->getPosition());
	//bool isCollision = collision->cubeCollisionSphere(collision->mCube[0], collision->mSphere[0]);
	//if (isCollision) {
	//	mSound->setPause(MusicIndex(BGM));
	//	hq->setLastFramePosition(hq->getLastFramePosition());
	//	hq->getTransform()->setPosition(hq->getLastFramePosition());
	//}
	//else {
	//	mSound->setReplay(MusicIndex(BGM));
	//	hq->setLastFramePosition(hq->getTransform()->getPosition());
	//}

#pragma region test code

	if (!mIsGameMode)
	{
		if (DInputPC::getInstance().iskeyDown(DIK_SPACE))
		{
			mIsGameMode = true;
		}
	}

	//if (DInputPC::getInstance().isMouseButtonDown(0)) {
	//	fireBullet = true;
	//	bullet = SceneManager::sGetInstance()->createSphere();
	//	bullet->setName("bullet");
	//	bullet->getTransform()->setPosition(tankBattery->getTransform()->getPosition() + tankBattery->getTransform()->Forward * 30.f
	//										+ tankBattery->getTransform()->Up * 10.f + tankBattery->getTransform()->Right * 2.f);  //Vector3(2.f, 10.f, 30.f)
	//	bullet->getTransform()->setScale(Vector3(1.f, 1.f, 1.f));
	//	bulletDirection = tankBattery->getTransform()->Forward;
	//}
	////Bullet Update
	//if (fireBullet) {
	//	bullet->getTransform()->translate(bulletDirection * deltaTime * 10.f);
	//}

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
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
#include "SoundManager.h"

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

	//SoundManagerInit
	SoundManager::onInit();

	//Rendering Init
	mRendering.get()->onInit();

	//eui creation
	mEui = std::make_unique<ImGuiFrame>(
		mWnd.getHwnd(), mRendering->getGFX()->getDevice(), mRendering->getGFX()->getContext());
}

void Engine::onInit()
{
	//Input Init
	DInputPC::getInstance().onInit(mWnd.getHwnd(), mWnd.getHinst(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );

	//Sound Init
	//mSound->onInit();

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

	//SoundManager Update
	SoundManager::sGetInstance()->onUpdate();

	if (mIsGameMode)
	{
		mGameSystem->onUpdate(deltaTime);
		//mSound->playBGM();
 		SoundManager::sGetInstance()->playSound(0);
	}


#pragma region test code

	if (!mIsGameMode)
	{
		if (DInputPC::getInstance().iskeyDown(DIK_SPACE))
		{
			mIsGameMode = true;
		}
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

HWND Engine::getHWND()
{
	return mWnd.getHwnd();
}

POINT Engine::getCursorPos()
{
	return mWnd.getCursorPosInWnd();
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
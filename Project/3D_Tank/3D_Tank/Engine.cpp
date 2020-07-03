#include <sstream>

#include "Engine.h"
#include "Window.h"
#include "SceneManager.h"
#include "ComponentFactory.h"
#include "Configuration.h"
#include "FileManager.h"


//test
#include "Rendering.h"
#include "Graphics.h"
#include "SoundManager.h"
#include "CollisionManager.h"
#include "ShellContainer.h"
#include "Collision.h"

Engine* Engine::sInstance = nullptr;

//test code

Engine::Engine(Window& wnd)
	:
	mWnd(wnd),
	mSound(std::make_unique<Sound>()),
	mRendering(std::make_unique<Rendering>(wnd)),
	mGameSystem(std::make_unique<GameSystem>()),
	mIsGameMode(true), mIsEditMode(false)
{
	onPreInit();

	onInit();

	onPostInit();
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

	CollisionManager::onInit();

	ShellContainer::onInit();

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


	//EUI Init
	mEui->onInit();

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
	 gSpeed = 1.0f;

#pragma endregion
}

void Engine::run()
{
	if (DInputPC::getInstance().iskeyDown(DIK_F4))
	{
		gSpeed = 4.0f;
	}
	if (DInputPC::getInstance().iskeyUp(DIK_F4))
	{
		gSpeed = 1.0f;
	}
	//Timer update
	mTimer.tick();
	float deltaTime = mTimer.getDeltaTIme() * gSpeed;
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
	}


#pragma region test code

	if (!mIsGameMode)
	{
		if (DInputPC::getInstance().iskeyDown(DIK_SPACE))
		{
			enableGameMode(true);
		}
	}

#pragma endregion


	//Sound Update
	//mSound->onUpdate(dis);

	//PreRender
	mRendering.get()->onPreRender(deltaTime);

	//OnRender
	mRendering.get()->onRender(deltaTime);

	//PostRender
	mRendering.get()->onPostRender(deltaTime);

	//gui update

	//eui update
	if (mIsEditMode)
	{
		mEui->onUpdate(deltaTime);
	}

	mRendering.get()->onEndRender(deltaTime);
}

void Engine::onPostInit()
{

	//Game Init
	mGameSystem->onInit();
}

float Engine::getTotalTime() noexcept
{
	return mTimer.getTotalTime();
}

float Engine::getDeltaTIme() noexcept
{
	return mTimer.getDeltaTIme();
}

HWND Engine::getHWND()
{
	return mWnd.getHwnd();
}

POINT Engine::getCursorPos()
{
	return mWnd.getCursorPosInWnd();
}

void Engine::enableEditMode(bool value)
{
	mIsEditMode = value;
}

void Engine::enableGameMode(bool value)
{
	mIsGameMode = value;
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
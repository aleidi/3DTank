#include <sstream>
#include <fstream>

#include "Engine.h"
#include "Window.h"
#include "SceneManager.h"
#include "ComponentFactory.h"
#include "Configuration.h"
#include "FileManager.h"
#include "Rendering.h"
#include "Graphics.h"
#include "SoundManager.h"
#include "CollisionManager.h"
#include "GameModeTP.h"
#include "GameLevelManager.h"
#include "RenderManager.h"
#include "PlayerTank.h"


Engine* Engine::sInstance = nullptr;

Engine::Engine(Window& wnd)
	:
	mWnd(wnd),
	mRendering(std::make_unique<Rendering>(wnd)),
	mGameSystem(std::make_unique<GameSystem>()),
	mIsGameMode(true), mIsEditMode(false),mRunSpeed(1.0f)
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

	//EUI Init
	mEui->onInit();
}

void Engine::onPostInit()
{
	//Game Init
	mGameSystem->onInit();
}

void Engine::run()
{
	//speed up and down
	if (DInputPC::getInstance().iskeyDown(DIK_F4))
	{
		mRunSpeed = 2.0f;
	}
	if (DInputPC::getInstance().iskeyUp(DIK_F4))
	{
		mRunSpeed = 1.0f;
	}
	if (DInputPC::getInstance().iskeyDown(DIK_F3))
	{
		mRunSpeed = 0.5f;
	}
	if (DInputPC::getInstance().iskeyUp(DIK_F3))
	{
		mRunSpeed = 1.0f;
	}

	if (DInputPC::getInstance().iskeyDown(DIK_F2))
	{
		recordCamraPosition();
	}

	//Timer update
	mTimer.tick();
	float deltaTime = mTimer.getDeltaTIme() * mRunSpeed;
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

	//Sound Update
	//mSound->onUpdate(dis);

	//PreRender
	mRendering.get()->onPreRender(deltaTime);

	//OnRender
	mRendering.get()->onRender(deltaTime);

	//PostRender
	mRendering.get()->onPostRender(deltaTime);

	//eui update
	if (mIsEditMode)
	{
		mEui->onUpdate(deltaTime);
	}

	mRendering.get()->onEndRender(deltaTime);

	//Garbage Collection
	SceneManager::sGetInstance()->onGarbageCollection();
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

void Engine::onResize(float width, float height)
{
	mRendering->onResize(width, height);
}

void Engine::changeRunSpeed(float value)
{
	mRunSpeed = value;
}

void Engine::startGame()
{
	GameLevelManager::sGetInstance()->resetCurrentGameMode();
	GameLevelManager::sGetInstance()->setCurrentGameMode(new GameModeTP());
	Camera::MainCamera = reinterpret_cast<PlayerTank*>(GameInstance::sGetInstance()->getPlayer())->getCamera();
	GameInstance::sGetInstance()->getPlayerController()->setEnable(true);
	reinterpret_cast<PlayerTank*>(GameInstance::sGetInstance()->getPlayer())->enableHUD(true);
	enableGameMode(true);
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

void Engine::recordCamraPosition()
{
	XMFLOAT3 pos;
	XMStoreFloat3(&pos, RenderManager::sGetInstance()->getGraphics().getCameraPosition());
	std::ofstream os;
	os.open("./Log/cameralog.txt", std::ios::app);
	os << "CameraPos:" << pos.x << ",";
	os << pos.y << ",";
	os << pos.z << ",";
	XMStoreFloat3(&pos, RenderManager::sGetInstance()->getGraphics().getCameraRotation());
	os << "CameraRot:" << pos.x << ",";
	os << pos.y << ",";
	os << pos.z << std::endl;
	os.close();
}

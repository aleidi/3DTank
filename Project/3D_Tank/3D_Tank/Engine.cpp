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
	// タイマーを初期化
	mTimer.reset();

	// SceneManagerを初期化
	SceneManager::createSingleton();

	// SoundManagerを初期化
	SoundManager::onInit();

	CollisionManager::onInit();

	// 描画を初期化
	mRendering.get()->onInit();

	// EUIを生成
	mEui = std::make_unique<ImGuiFrame>(
		mWnd.getHwnd(), mRendering->getGFX()->getDevice(), mRendering->getGFX()->getContext());
}

void Engine::onInit()
{
	// 入力を初期化
	DInputPC::getInstance().onInit(mWnd.getHwnd(), mWnd.getHinst(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );

	// EUIを初期化
	mEui->onInit();
}

void Engine::onPostInit()
{
	// ゲームを初期化
	mGameSystem->onInit();
}

void Engine::run()
{
	// 速度を増減
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

	// タイマーを更新
	mTimer.tick();
	float deltaTime = mTimer.getDeltaTIme() * mRunSpeed;
	calculateFrameStats();

	// 入力を更新
	DInputPC::getInstance().onUpdate();

	// 物理処理を更新
	SceneManager::sGetInstance()->onEngineFixedUpdate(FixedDeltaTime);

	// ゲームを更新
	SceneManager::sGetInstance()->onEngineUpdate(deltaTime);

	// SoundManagerを更新
	SoundManager::sGetInstance()->onUpdate();

	if (mIsGameMode)
	{
		mGameSystem->onUpdate(deltaTime);
	}

	// サウンドを更新
	//mSound->onUpdate(dis);

	// 描画前処理
	mRendering.get()->onPreRender(deltaTime);

	// 描画処理
	mRendering.get()->onRender(deltaTime);

	// 描画後処理
	mRendering.get()->onPostRender(deltaTime);

	// EUIを更新
	if (mIsEditMode)
	{
		mEui->onUpdate(deltaTime);
	}

	mRendering.get()->onEndRender(deltaTime);

	// ガベージコレクション
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
		const float fps = static_cast<float>(frameCnt);
		const float mspf = (fps > 0.0f) ? (1000.0f / fps) : 0.0f;

		wchar_t title[256] = {};
		swprintf_s(title, L"3D Tank   FPS: %.2f   Frame Time: %.2f (ms)", fps, mspf);
		SetWindowTextW(mWnd.getHwnd(), title);

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

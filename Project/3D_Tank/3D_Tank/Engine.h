#pragma once
#include "Timer.h"
#include "Sound.h"
#include "Rendering.h"
#include "GameSystem.h"
#include "ImGuiFrame.h"

class Window;

class Engine
{
public:
	static Engine* sGetInstance();
	static void createSingleton(Window& wnd);
	static void Destroy();

	void onPreInit();
	void onInit();
	void run();

	POINT getCursorPos();
	void showtText(const std::wstring& str, float leftTopX, float leftTopY, float width, float height,bool canShow);
private:
	Engine(Window& wnd);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
	void calculateFrameStats();

private:
	static Engine* sInstance;

	friend class ImGuiFrame;

	Window& mWnd;
	std::unique_ptr<Sound> mSound;
	std::unique_ptr<Rendering> mRendering;
	Timer mTimer;
	std::unique_ptr<GameSystem> mGameSystem;
	std::unique_ptr<ImGuiFrame> mEui;

	bool mIsGameMode;

	//testcode
	float fScale;
	float fTrans_x;
	float fTrans_y;
	float fTrans_z;
	float fRot_x;
	float fRot_y;
	float fRot_z;
	float fspeed;
	float rspeed;
};


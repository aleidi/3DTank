
#pragma once
#include "Timer.h"
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
	void onPostInit();

	float getTotalTime() noexcept;
	float getDeltaTIme() noexcept;
	HWND getHWND();
	POINT getCursorPos();
	void enableEditMode(bool value);
	void enableGameMode(bool value);
	void onResize(float width, float height);
	void changeRunSpeed(float value);
	void startGame();

	void showtText(const std::wstring& str, float leftTopX, float leftTopY, float width, float height,bool canShow);
private:
	Engine(Window& wnd);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
	void calculateFrameStats();
	void recordCamraPosition();

private:
	static Engine* sInstance;

	friend class ImGuiFrame;

	Window& mWnd;
	std::unique_ptr<Rendering> mRendering;
	Timer mTimer;
	std::unique_ptr<GameSystem> mGameSystem;
	std::unique_ptr<ImGuiFrame> mEui;

	bool mIsGameMode;
	bool mIsEditMode;
	float mRunSpeed;
};


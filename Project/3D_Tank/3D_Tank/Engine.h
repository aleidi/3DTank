#pragma once
#include "Timer.h"
#include "Sound.h"
#include "Rendering.h"

#if defined(PS4)
#include "DInput_PS4.h"
#else
#include "DInput_PC.h"
#endif

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class Window;

class Engine
{
public:
	Engine(Window& wnd);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	void OnInit();
	void run();
private:
	void calculateFrameStats();

private:
	Window& mWnd;
	std::unique_ptr<Sound> mSound;
	std::unique_ptr<Rendering> mRendering;
	Timer mTimer;

	//testcode
	float fScale;
	float fTrans_x;
	float fTrans_y;
	float fTrans_z;

};


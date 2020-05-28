#pragma once
#include "Timer.h"

#if defined(PS4)
#include "DInput_PS4.h"
#else
#include "DInput_PC.h"
#endif

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class Window;
class Graphics;

class Engine
{
public:
	Engine(Window& wnd);
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	void run();
private:
	void calculateFrameStats();

private:
	Window& mWnd;
	Graphics* mGraphics;
	Timer mTimer;
	float fScale;
	float fTrans_x;
	float fTrans_y;
	float fTrans_z;

};


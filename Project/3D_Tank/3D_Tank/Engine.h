#pragma once
#include "Timer.h"

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
};


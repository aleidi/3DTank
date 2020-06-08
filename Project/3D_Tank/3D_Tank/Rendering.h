#pragma once
#include "EngineCommon.h"

class Window;
class Graphics;
class RenderComponent;

class Rendering
{
public:
	Rendering(Window& wnd);
	~Rendering();

	void onInit();
	void onPreRender(float deltaTime);
	void onRender(float deltaTime);
	void onPostRender(float deltaTime);
	void onEndRender(float deltaTime);

	//test code
	Graphics* getGFX();

private:
	Graphics* mGraphics;
	Window* mhMainWnd;
};
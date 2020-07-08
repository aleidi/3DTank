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
	void onPreRender(const float& deltaTime);
	void onRender(const float& deltaTime);
	void onPostRender(const float& deltaTime);
	void onEndRender(const float& deltaTime);

	void onResize(const float& width, const float& height);

	//test code
	Graphics* getGFX();

private:
	Graphics* mGraphics;
	Window* mhMainWnd;
};
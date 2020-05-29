#pragma once
#include "EngineCommon.h"

class Window;
class Graphics;
class Drawable3D;

class Rendering
{
public:
	Rendering(Window& wnd);
	~Rendering();

	void onInit();
	void onPreRender(float deltaTime);
	void onRender(float deltaTime);
	void onPostRender(float deltaTime);

	void AddDrawable(Drawable3D* drawable) noexcept;

	//test code
	Graphics* getGFX();

private:
	Graphics* mGraphics;
	Window* mhMainWnd;
	std::vector<Drawable3D*> mObjects3D;
};
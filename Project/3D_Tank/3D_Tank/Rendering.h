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

	void addDrawable3D(Drawable3D* drawable) noexcept;
	void removeDrawable3D(Drawable3D* drawable);
	//test code
	Graphics* getGFX();

private:
	Graphics* mGraphics;
	Window* mhMainWnd;
	std::map<UINT,Drawable3D*> mObjects3D;
};
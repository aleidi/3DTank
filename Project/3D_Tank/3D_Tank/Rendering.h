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

	void addDrawing(RenderComponent* drawComp) noexcept;
	void removeDrawing(UINT id);
	UINT registerID() noexcept;

	//test code
	Graphics* getGFX();

private:


	Graphics* mGraphics;
	Window* mhMainWnd;

	std::vector<RenderComponent*> mDrawings;
	UINT mDrawingID;
};
#include "Rendering.h"
#include "Window.h"
#include "Drawable.h"

Rendering::Rendering(Window & wnd)
	:mhMainWnd(&wnd),mDrawings()
{
}

Rendering::~Rendering()
{
}

void Rendering::onInit()
{
	mGraphics = new Graphics(*mhMainWnd);
}

void Rendering::onPreRender(float deltaTime)
{
	mGraphics->CleanFrame();
}

void Rendering::onRender(float deltaTime)
{
}

void Rendering::onPostRender(float deltaTime)
{
	mGraphics->showText();

	mGraphics->EndFrame();
}

void Rendering::addDrawing(RenderComponent * drawComp) noexcept
{
	mDrawings.push_back(drawComp);
}

void Rendering::removeDrawing(UINT id)
{
	delete mDrawings[id];
	mDrawings[id] = nullptr;
}


UINT Rendering::registerID() noexcept
{
	return 0;
}

Graphics * Rendering::getGFX()
{
	return mGraphics;
}

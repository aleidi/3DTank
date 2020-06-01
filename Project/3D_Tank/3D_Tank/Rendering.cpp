#include "Rendering.h"
#include "Window.h"
#include "Drawable3D.h"

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
	mGraphics->ShowText(L"fuck!fuck!fuck!", 100.0f, 100.0f, 200.0f, 200.0f);

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

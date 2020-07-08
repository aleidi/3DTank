#include "Rendering.h"
#include "Window.h"
#include "Drawable.h"
#include "RenderManager.h"
#include "RenderCamera.h"

Rendering::Rendering(Window & wnd)
	:mhMainWnd(&wnd)
{
}

Rendering::~Rendering()
{
}

void Rendering::onInit()
{
	mGraphics = new Graphics(*mhMainWnd);

	RenderManager::createSingleton(*mGraphics);
}

void Rendering::onPreRender(const float& deltaTime)
{
	mGraphics->onUdpate(deltaTime);

	mGraphics->CleanFrame();
}

void Rendering::onRender(const float& deltaTime)
{
	RenderManager::sGetInstance()->onDraw();
}

void Rendering::onPostRender(const float& deltaTime)
{
	mGraphics->DrawSkyBox();

	RenderManager::sGetInstance()->onPostDraw(deltaTime);

	mGraphics->showText();
}

void Rendering::onEndRender(const float& deltaTime)
{
	mGraphics->EndFrame();
}

void Rendering::onResize(const float& width, const float& height)
{
	mGraphics->OnResize(width, height);
}

Graphics * Rendering::getGFX()
{
	return mGraphics;
}

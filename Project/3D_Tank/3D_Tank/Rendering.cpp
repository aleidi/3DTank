#include "Rendering.h"
#include "Window.h"
#include "Drawable.h"
#include "RenderManager.h"
#include "RenderCamera.h"

#include "UIText.h"

UIText* txt;

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

	txt = new UIText(*mGraphics);
}

void Rendering::onPreRender(float deltaTime)
{
	mGraphics->onUdpate(deltaTime);

	mGraphics->CleanFrame();
}

void Rendering::onRender(float deltaTime)
{
	RenderManager::sGetInstance()->onDraw();
}

void Rendering::onPostRender(float deltaTime)
{
	mGraphics->DrawSkyBox();

	RenderManager::sGetInstance()->onPostDraw();
	txt->draw(*mGraphics);

	//mGraphics->showText();
}

void Rendering::onEndRender(float deltaTime)
{
	mGraphics->EndFrame();
}

Graphics * Rendering::getGFX()
{
	return mGraphics;
}

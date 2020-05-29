#include "Rendering.h"
#include "Window.h"
#include "Drawable3D.h"

Rendering::Rendering(Window & wnd)
	:mhMainWnd(&wnd), mObjects3D()
{
}

Rendering::~Rendering()
{
	for (std::vector<Drawable3D*>::iterator it = mObjects3D.begin(); it != mObjects3D.end(); ++it)
	{
		if (nullptr != *it)
		{
			delete *it;
			*it = nullptr;
		}
	}
	mObjects3D.clear();
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
	for (std::vector<Drawable3D*>::iterator it = mObjects3D.begin(); it != mObjects3D.end(); ++it)
	{
		(*it)->Draw(*mGraphics);
	}
}

void Rendering::onPostRender(float deltaTime)
{
	mGraphics->EndFrame();
}

void Rendering::AddDrawable(Drawable3D* drawable) noexcept
{
	mObjects3D.push_back(drawable);
}

Graphics * Rendering::getGFX()
{
	return mGraphics;
}

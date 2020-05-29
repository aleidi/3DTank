#include "Rendering.h"
#include "Window.h"
#include "Drawable3D.h"

Rendering::Rendering(Window & wnd)
	:mhMainWnd(&wnd), mObjects3D()
{
}

Rendering::~Rendering()
{
	for (std::map<UINT,Drawable3D*>::iterator it = mObjects3D.begin(); it != mObjects3D.end(); ++it)
	{
		if (nullptr != it->second)
		{
			delete it->second;
			it->second = nullptr;
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
	for (std::map<UINT, Drawable3D*>::iterator it = mObjects3D.begin(); it != mObjects3D.end(); ++it)
	{
		if (nullptr == it->second)
		{
			continue;
		}
		it->second->Draw(*mGraphics);
	}
}

void Rendering::onPostRender(float deltaTime)
{
	mGraphics->EndFrame();
}

void Rendering::addDrawable3D(Drawable3D * drawable) noexcept
{
	mObjects3D[drawable->getID()]= drawable;
}

void Rendering::removeDrawable3D(Drawable3D * drawable)
{
	int id = drawable->getID();
	delete mObjects3D[id];
	mObjects3D[id] = nullptr;
	mObjects3D.erase(id);
}

Graphics * Rendering::getGFX()
{
	return mGraphics;
}

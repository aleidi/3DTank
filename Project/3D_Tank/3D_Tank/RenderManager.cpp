#include "RenderManager.h"

RenderManager* RenderManager::sInstance = nullptr;

RenderManager * RenderManager::sGetInstance()
{
	return sInstance;
}

void RenderManager::createSingleton(Graphics & gfx)
{
	assert(!sInstance);
	sInstance = new RenderManager(gfx);
}

void RenderManager::Destroy()
{
	delete sInstance;
	sInstance = nullptr;
}

void RenderManager::addMeshToPool(Mesh * mesh)
{
	mMeshes.push_back(mesh);
}

void RenderManager::removeMeshFromPool(Mesh * mesh)
{
	for (std::list<Mesh*>::iterator it = mMeshes.begin(); it != mMeshes.end();)
	{
		if (*it == mesh)
		{
			delete *it;
			*it = nullptr;
			mMeshes.erase(it++);
		}
		else
		{
			++it;
		}
	}
}

Graphics & RenderManager::getGraphics() const
{
	return mGraphics;
}

RenderManager::RenderManager(Graphics & gfx)
	:mMeshes(),mGraphics(gfx)
{
}

RenderManager::~RenderManager()
{
	for (std::list<Mesh*>::iterator it = mMeshes.begin(); it != mMeshes.end(); ++it)
	{
		if (nullptr != *it)
		{
			delete *it;
			*it = nullptr;
		}
	}
	mMeshes.clear();
}

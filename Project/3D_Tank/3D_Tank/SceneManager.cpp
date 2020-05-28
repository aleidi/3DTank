#include "SceneManager.h"

SceneManager SceneManager::instance;

SceneManager::SceneManager()
	:mObjsID(0),mCompsID(0),mObjs(),mComps()
{
}

SceneManager::~SceneManager()
{
}

Gameobject * SceneManager::createCube() const noexcept
{
	return nullptr;
}

Gameobject * SceneManager::createSphere() const noexcept
{
	return nullptr;
}

Gameobject * SceneManager::createPlane() const noexcept
{
	return nullptr;
}

Gameobject * SceneManager::createEmptyObject() const noexcept
{
	return nullptr;
}

Transform * SceneManager::createTransform() const noexcept
{
	return nullptr;
}

RenderComponent * SceneManager::createRender() const noexcept
{
	return nullptr;
}

void SceneManager::destroyGameobject(UINT id) noexcept
{
	delete mObjs[id];
	mObjs[id] = nullptr;
}

void SceneManager::destroyComponent(UINT id) noexcept
{
	delete mComps[id];
	mComps[id] = nullptr;
}

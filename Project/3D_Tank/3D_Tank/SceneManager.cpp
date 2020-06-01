#include "SceneManager.h"

SceneManager SceneManager::instance;

SceneManager::SceneManager()
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

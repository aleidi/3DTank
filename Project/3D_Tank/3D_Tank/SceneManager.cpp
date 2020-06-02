#include <assert.h>
#include "SceneManager.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "FactoryBase.h"

SceneManager* SceneManager::sInstance = nullptr;

SceneManager::SceneManager()
	:mObjs(),mFactories()
{
	mFactories["Cube"] = new CubeObjectFactory();
	mFactories["Sphere"] = new SphereObjectFactory();
	mFactories["Plane"] = new PlaneObjectFactory();
}

SceneManager::~SceneManager()
{
	for (std::list<GameObject*>::iterator it = mObjs.begin(); it != mObjs.end(); ++it)
	{
		if (nullptr != *it)
		{
			delete *it;
			*it = nullptr;
		}
	}
	mObjs.clear();
}

SceneManager * SceneManager::sGetInstance()
{
	return sInstance;
}

void SceneManager::createSingleton()
{
	assert(!sInstance);
	sInstance = new SceneManager();
}

GameObject * SceneManager::createCube() const noexcept
{
	return mFactories.at("Cube")->getObject();
}

GameObject * SceneManager::createSphere() const noexcept
{
	return mFactories.at("Sphere")->getObject();
}

GameObject * SceneManager::createPlane() const noexcept
{
	return mFactories.at("Plane")->getObject();
}

GameObject * SceneManager::createEmptyObject() const noexcept
{
	return nullptr;
}

void SceneManager::createRenderComponent(GameObject * object) const noexcept
{
}

void SceneManager::addGameObjectToPool(GameObject * object) noexcept
{
	mObjs.push_back(object);
}

bool SceneManager::removeGameObjectToPool(GameObject * object) noexcept
{
	for (std::list<GameObject*>::iterator it = mObjs.begin(); it != mObjs.end();)
	{
		if (*it == object)
		{
			delete *it;
			*it = nullptr;
			mObjs.erase(it++);
			return true;
		}
		else
		{
			++it;
		}
	}
	return false;
}

void SceneManager::onUpdate(float deltaTime)
{
	for (std::list<GameObject*>::iterator it = mObjs.begin(); it != mObjs.end(); ++it)
	{
		if (nullptr != *it)
		{
			(*it)->onUpdate(deltaTime);
		}
	}
}

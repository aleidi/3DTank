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
	mFactories["Empty"] = new EmptyObjectFactory();
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
	return mFactories.at("Empty")->getObject();
}

void SceneManager::createRenderComponent(GameObject * object) const noexcept
{
}

void SceneManager::createModel(GameObject & obj, const std::string & modelPath, const std::wstring & texturePath)
{
	ComponentFactory::createModel(obj, modelPath, texturePath);
}

void SceneManager::createModel(GameObject & obj, const std::string & modelPath, const std::wstring & texturePath, DirectX::XMVECTOR & maxPoint, DirectX::XMVECTOR & minPoint)
{
	ComponentFactory::createModel(obj, modelPath, texturePath, maxPoint, minPoint);
}

void SceneManager::addGameObjectToPool(GameObject * object) noexcept
{
	mObjs.push_back(object);
}

bool SceneManager::removeGameObjectFromPool(GameObject * object) noexcept
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

GameObject * SceneManager::findObjectWithName(const std::string & name)
{
	for (std::list<GameObject*>::iterator it = mObjs.begin(); it != mObjs.end(); ++it)
	{
		if ((*it)->getName() == name)
		{
			return *it;
		}
	}

	return nullptr;
}

std::list<std::string> SceneManager::getAllGameobjectName()
{
	std::list<std::string> nList;
	
	for (std::list<GameObject*>::iterator it = mObjs.begin(); it != mObjs.end(); ++it)
	{
		nList.push_back((*it)->getName());
	}

	return nList;
}

void SceneManager::onGameStart()
{
	for (std::list<GameObject*>::iterator it = mObjs.begin(); it != mObjs.end(); ++it)
	{
		if (nullptr != *it && (*it)->hasParent() != true)
		{
			(*it)->onStart();
		}
	}
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

void SceneManager::onEngineUpdate(float deltaTime)
{
	for (std::list<GameObject*>::iterator it = mObjs.begin(); it != mObjs.end(); ++it)
	{
		if (nullptr != *it && (*it)->hasParent() != true)
		{
			(*it)->onEngineUpdate(deltaTime);
		}
	}
}

void SceneManager::onEngineFixedUpdate(float fixedDeltaTime)
{
	for (std::list<GameObject*>::iterator it = mObjs.begin(); it != mObjs.end(); ++it)
	{
		if (nullptr != *it && (*it)->hasParent() != true)
		{
			(*it)->onEngineFixedUpdate(fixedDeltaTime);
		}
	}
}

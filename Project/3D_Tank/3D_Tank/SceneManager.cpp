#include <assert.h>

#include "SceneManager.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "FactoryBase.h"
#include "RenderManager.h"
#include "UIImage.h"
#include "UIButton.h"
#include "UIText.h"
#include "UIImage3D.h"
#include "RenderManager.h"
#include "AIController.h"

SceneManager* SceneManager::sInstance = nullptr;

SceneManager::SceneManager()
	:mObjs(),mAIControllers(),mFactories()
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

GameObject * SceneManager::createCube() noexcept
{
	return mFactories.at("Cube")->getObject();
}

GameObject * SceneManager::createSphere() noexcept
{
	return mFactories.at("Sphere")->getObject();
}

GameObject * SceneManager::createPlane() noexcept
{
	return mFactories.at("Plane")->getObject();
}

GameObject * SceneManager::createEmptyObject() noexcept
{
	return mFactories.at("Empty")->getObject();
}

void SceneManager::createRenderComponent(GameObject * object) noexcept
{
}

RenderComponent* SceneManager::createModel(GameObject & obj, const std::string & modelPath, const std::wstring & texturePath)
{
	return ComponentFactory::createModel(obj, modelPath, texturePath);
}

RenderComponent* SceneManager::createModel(GameObject & obj, const std::string & modelPath, const std::wstring & texturePath, DirectX::XMVECTOR & maxPoint, DirectX::XMVECTOR & minPoint)
{
	return ComponentFactory::createModel(obj, modelPath, texturePath, maxPoint, minPoint);
}

UIImage* SceneManager::createUIImage(const std::wstring& texPath)
{
	UIImage* ui = new UIImage(RenderManager::sGetInstance()->getGraphics(),texPath);
	RenderManager::sGetInstance()->addUIToPool(ui);
	return ui;
}

UIButton* SceneManager::createUIButton(const std::wstring & texPath)
{
	UIButton* ui = new UIButton(RenderManager::sGetInstance()->getGraphics(), texPath);
	RenderManager::sGetInstance()->addUIToPool(ui);
	return ui;
}

UIText * SceneManager::createUIText()
{
	UIText* ui = new UIText(RenderManager::sGetInstance()->getGraphics());
	RenderManager::sGetInstance()->addUIToPool(ui);
	return ui;
}

UIImage3D * SceneManager::createUIImage3D(const std::wstring & texPath)
{
	UIImage3D* ui = new UIImage3D(RenderManager::sGetInstance()->getGraphics(), texPath);
	RenderManager::sGetInstance()->addUI3DToPool(ui);
	return ui;
}

AIController * SceneManager::createAIController(int id)
{
	AIController* ac = new AIController(id);
	mAIControllers[id] = ac;
	return ac;
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

bool SceneManager::removeAIControllerFromPool(AIController * ctrl) noexcept
{
	for (std::map<int,AIController*>::iterator it = mAIControllers.begin(); it != mAIControllers.end();)
	{
		if ((*it).second == ctrl)
		{
			delete (*it).second;
			(*it).second = nullptr;
			mAIControllers.erase(it++);
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

AIController * SceneManager::getAIController(int id)
{
	for (std::map<int, AIController*>::iterator it = mAIControllers.begin(); it != mAIControllers.end(); ++it)
	{
		if ((*it).first == id)
		{
			return (*it).second;
		}
	}
	return nullptr;
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

void SceneManager::onLateUpdate(float deltaTime)
{
	for (std::list<GameObject*>::iterator it = mObjs.begin(); it != mObjs.end(); ++it)
	{
		if (nullptr != *it && (*it)->hasParent() != true)
		{
			(*it)->onLateUpdate(deltaTime);
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

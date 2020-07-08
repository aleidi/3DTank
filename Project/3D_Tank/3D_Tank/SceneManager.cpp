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
#include "ParticleSystem.h"
#include "UIText3D.h"
#include "VFXSphere.h"

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

UIText * SceneManager::createUIText(const std::wstring& text)
{
	UIText* ui = new UIText(RenderManager::sGetInstance()->getGraphics(), text);
	RenderManager::sGetInstance()->addUIToPool(ui);
	return ui;
}

UIImage3D * SceneManager::createUIImage3D(const std::wstring & texPath, bool isSP)
{
	UIImage3D* ui = new UIImage3D(RenderManager::sGetInstance()->getGraphics(), texPath);
	RenderManager::sGetInstance()->addUI3DToPool(ui, isSP);
	return ui;
}

UIText3D * SceneManager::createUIText3D(const std::wstring& text)
{
	UIText3D* ui = new UIText3D(RenderManager::sGetInstance()->getGraphics(), text);
	RenderManager::sGetInstance()->addUI3DToPool(ui);
	return ui;
}

ParticleSystem * SceneManager::createParticleSystem(const std::wstring & texPath,int maxParticles)
{
	ParticleSystem* p = new ParticleSystem(RenderManager::sGetInstance()->getGraphics(), texPath, maxParticles);
	RenderManager::sGetInstance()->addParticleToPool(p);
	return p;
}

VFXSphere * SceneManager::createVFXSphere()
{
	VFXSphere* s = new VFXSphere(RenderManager::sGetInstance()->getGraphics());
	RenderManager::sGetInstance()->addVFXToPool(s);
	return s;
}

void SceneManager::setSkyBox(const std::wstring & texPath)
{
	RenderManager::sGetInstance()->setSkyBox(texPath);
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

bool SceneManager::removreUIFromPool(UIBase * ui)
{
	if (RenderManager::sGetInstance()->removeUIFromPool(ui))
	{
		return true;
	}
	return false;
}

bool SceneManager::removeUI3DFromPool(UIBase * ui, bool isSP)
{
	if (RenderManager::sGetInstance()->removeUI3DFromPool(ui, isSP))
	{
		return true;
	}
	return false;
}

bool SceneManager::removeParticleFromPool(ParticleSystem * particle)
{
	if (RenderManager::sGetInstance()->removeParticleFromPool(particle))
	{
		return true;
	}
	return false;
}

bool SceneManager::removeVFXSphereFromPool(VFXSphere * s)
{
	if (RenderManager::sGetInstance()->removeVFXFromPool(s))
	{
		return true;
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
		if (*it != nullptr)
		{
			nList.push_back((*it)->getName());
		}
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
			if ((*it)->hasParent() != true)
			{
				(*it)->onUpdate(deltaTime);
			}
		}
	}

	for (std::map<int,AIController*>::iterator it = mAIControllers.begin(); it != mAIControllers.end(); ++it)
	{
		if (nullptr != (*it).second)
		{
			if ((*it).second->hasParent() != true)
			{
				(*it).second->onUpdate(deltaTime);
			}
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

void SceneManager::onGarbageCollection()
{
	if (mGarbageObjs.size() != 0)
	{
		for (std::list<GameObject*>::iterator it = mGarbageObjs.begin(); it != mGarbageObjs.end();)
		{
				removeGameObjectFromPool(*it);
				*it = nullptr;
				mGarbageObjs.erase(it++);
		}
	}
}

void SceneManager::registerGarbageObj(GameObject * obj)
{
	for (std::list<GameObject*>::iterator it = mGarbageObjs.begin(); it != mGarbageObjs.end(); ++it)
	{
		if (*it != obj)
		{
			continue;
		}
		else
		{
			return;
		}
	}
	mGarbageObjs.push_back(obj);
}

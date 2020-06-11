#include <typeinfo>
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "SceneManager.h"
#include "ScriptComponent.h"

GameObject::GameObject()
	:mTransform(new Transform(this)),mName("GameObject")
{
	SceneManager::sGetInstance()->addGameObjectToPool(this);
}

GameObject::~GameObject()
{
	for (std::list<Component*>::iterator it = mComps.begin(); it != mComps.end(); ++it)
	{
		if (nullptr != *it)
		{
			delete *it;
			*it = nullptr;
		}
	}
	mComps.clear();
	if (lastFramePostion != NULL)
	{
		delete lastFramePostion;
		lastFramePostion = NULL;
	}
}

void GameObject::addComponent(Component * comp) noexcept
{
	mComps.push_back(comp);
}

void GameObject::addScriptComponent(ScriptComponent * comp) noexcept
{
	mComps.push_front(dynamic_cast<Component*>(comp));
}

bool GameObject::removeComponent(Component * comp)
{
	for (std::list<Component*>::iterator it = mComps.begin(); it != mComps.end();)
	{
		if (*it == comp)
		{
			delete *it;
			*it = nullptr;
			mComps.erase(it++);
			return true;
		}
		else
		{
			++it;
		}
	}
	return false;
}

template<class T>
T * GameObject::getComponent(T* t) const noexcept
{
	for (std::list<Component*>::iterator it = mComps.begin(); it != mComps.end(); ++it)
	{
		if (*it == t)
		{
			return *it;
		}
	}
	return nullptr;
}

Transform * GameObject::getTransform() const noexcept
{
	return mTransform;
}

std::string GameObject::getName() const noexcept
{
	return mName;
}

void GameObject::setName(const std::string & name) noexcept
{
	mName = name;
}

GameObject * GameObject::find(const std::string & name)
{
	return SceneManager::sGetInstance()->findObjectWithName(name);
}

void GameObject::attach(const GameObject & obj) noexcept
{
	obj.getTransform()->addChild(mTransform);
	mTransform->addParent(obj.getTransform());
}

void GameObject::attach(Transform & transform) noexcept
{
	transform.addChild(mTransform);
	mTransform->addParent(&transform);
}

bool GameObject::hasParent() noexcept
{
	auto i = mTransform->getParent();
	return (i != nullptr);
}

void GameObject::deAttach() noexcept
{
	mTransform->removeParent();
}

void GameObject::onStart()
{
	for (std::list<Component*>::iterator it = mComps.begin(); it != mComps.end(); ++it)
	{
		(*it)->onStart();
	}
}

void GameObject::onUpdate(float deltaTime)
{
	for (std::list<Component*>::iterator it = mComps.begin(); it != mComps.end(); ++it)
	{
		(*it)->onUpdate(deltaTime);
	}
	mTransform->onUpdate(deltaTime);
}

void GameObject::onEngineUpdate(float deltaTime)
{
	for (std::list<Component*>::iterator it = mComps.begin(); it != mComps.end(); ++it)
	{
		(*it)->onEngineUpdate(deltaTime);
	}
	mTransform->onEngineUpdate(deltaTime);
}

void GameObject::onEngineFixedUpdate(float fixedDeltaTime)
{
	for (std::list<Component*>::iterator it = mComps.begin(); it != mComps.end(); ++it)
	{
		(*it)->onEngineFixedUpdate(fixedDeltaTime);
	}
}

void GameObject::setLastFramePosition(const Vector3& position)
{
	lastFramePostion = new Vector3(position.x, position.y, position.z);
}

Vector3 GameObject::getLastFramePosition()
{
	return *lastFramePostion;
}

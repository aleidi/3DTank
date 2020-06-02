#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "SceneManager.h"

GameObject::GameObject()
	:mTransform(new Transform(this))
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
}

void GameObject::addComponent(Component * comp) noexcept
{
	mComps.push_back(comp);
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

void GameObject::onUpdate(float deltaTime) noexcept
{
	for (std::list<Component*>::iterator it = mComps.begin(); it != mComps.end(); ++it)
	{
		(*it)->onUpdate(deltaTime);
	}
}

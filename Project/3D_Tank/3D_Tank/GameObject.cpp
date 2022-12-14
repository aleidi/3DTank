#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "SceneManager.h"
#include "ScriptComponent.h"
#include "RenderComponent.h"

GameObject::GameObject()
	:mTransform(new Transform(this)),mName("GameObject"),mTag(ObjectTag::Environment)
{
	SceneManager::sGetInstance()->addGameObjectToPool(this);
}

GameObject::GameObject(int value)
	:mTransform(new Transform(this)), mName("GameObject"), mTag(ObjectTag::Environment)
{
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

GameObject::GameObject(GameObject & obj)
{
	mName = obj.mName;
	mTransform = new Transform(this);
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

void GameObject::enableDraw(bool value)
{
	for (std::list<Component*>::iterator it = mComps.begin(); it != mComps.end(); ++it)
	{
		RenderComponent* rc = dynamic_cast<RenderComponent*>(*it);
		if (rc != nullptr)
		{
			rc->enableDraw(value);
		}
	}
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

void GameObject::destroy()
{
	SceneManager::sGetInstance()->registerGarbageObj(this);
}

void GameObject::onStart()
{
	for (std::list<Component*>::iterator it = mComps.begin(); it != mComps.end(); ++it)
	{
		(*it)->onStart();
	}
}

void GameObject::onUpdate(const float& deltaTime)
{
	for (std::list<Component*>::iterator it = mComps.begin(); it != mComps.end(); ++it)
	{
		(*it)->onUpdate(deltaTime);
	}
	mTransform->onUpdate(deltaTime);
}

void GameObject::onLateUpdate(const float& deltaTime)
{
	for (std::list<Component*>::iterator it = mComps.begin(); it != mComps.end(); ++it)
	{
		(*it)->onLateUpdate(deltaTime);
	}
	mTransform->onLateUpdate(deltaTime);
}

void GameObject::onEngineUpdate(const float& deltaTime)
{
	for (std::list<Component*>::iterator it = mComps.begin(); it != mComps.end(); ++it)
	{
		(*it)->onEngineUpdate(deltaTime);
	}
	mTransform->onEngineUpdate(deltaTime);
}

void GameObject::onEngineFixedUpdate(const float& fixedDeltaTime)
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

GameObject::CollisionLayer GameObject::getCollisionLayer()  const
{
	return mColLayer;
}

GameObject::ObjectTag GameObject::getTag()  const
{
	return mTag;
}

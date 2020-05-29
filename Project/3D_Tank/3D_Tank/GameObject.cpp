#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	for (std::vector<Component*>::iterator it = mComps.begin(); it != mComps.end(); ++it)
	{
		if (nullptr != *it)
		{
			delete *it;
			*it = nullptr;
		}
	}
	mComps.clear();
}

void GameObject::setID(UINT id) noexcept
{
	mID = id;
}

UINT GameObject::getID() const noexcept
{
	return mID;
}

void GameObject::addComponent(Component * comp) noexcept
{
	mComps.push_back(comp);
}

Component * GameObject::getComponent(int index) const noexcept
{
	return mComps[index];
}

Transform * GameObject::getTransform() const noexcept
{
	return reinterpret_cast<Transform*>(mComps[0]);
}

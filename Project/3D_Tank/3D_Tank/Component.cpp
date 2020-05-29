#include "Component.h"

Component::Component()
	:mID(0),mObject(nullptr)
{
}

Component::~Component()
{
	mObject = nullptr;
}

void Component::setObject(GameObject * obj) noexcept
{
	mObject = obj;
}

GameObject * Component::getObject() const noexcept
{
	return mObject;
}

void Component::setID(UINT id) noexcept
{
	mID = id;
}

UINT Component::getID() const noexcept
{
	return mID;
}

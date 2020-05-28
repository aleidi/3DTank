#include "Component.h"

Component::Component()
{
}

Component::~Component()
{
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

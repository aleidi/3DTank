#include "Component.h"

Component::Component(GameObject * object)
	:mObject(object)
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
#include "Component.h"

Component::Component(GameObject * object) noexcept
	:mObject(object)
{
}

Component::~Component()
{
	mObject = nullptr;
}

GameObject * Component::getObject() const noexcept
{
	return mObject;
}
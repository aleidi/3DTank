#include "ScriptComponent.h"
#include "GameObject.h"

ScriptComponent::ScriptComponent(GameObject * object) noexcept
	:Component(object)
{
	mTransform = object->getTransform();
}

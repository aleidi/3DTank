#pragma once
#include "Component.h"

class Transform;

class ScriptComponent : public Component
{
public:
	ScriptComponent(GameObject* object) noexcept;
protected:
	Transform* mTransform;
};
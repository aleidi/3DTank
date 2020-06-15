#pragma once
#include "Component.h"
#include "Transform.h"

class MovementComponent : public Component
{
public:
	MovementComponent() = delete;
	MovementComponent(GameObject* object);
	virtual ~MovementComponent();

	void addVelocity(Vector3 value) noexcept;
	void addForce(Vector3 value) noexcept;

protected:
	Transform* mTransform;
};


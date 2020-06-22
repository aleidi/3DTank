#pragma once
#include "Component.h"
#include "Transform.h"

class MovementComponent : public Component
{
public:
	MovementComponent() = delete;
	MovementComponent(GameObject* object);
	virtual ~MovementComponent();

	virtual void onUpdate(float deltaTime);

	virtual void addVelocity(Vector3 value) = 0;
	virtual void addForce(Vector3 value) = 0;

protected:
	Transform* mTransform;
};


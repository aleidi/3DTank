#pragma once
#include "Component.h"
#include "Transform.h"

class MovementComponent : public Component
{
public:
	MovementComponent() = delete;
	MovementComponent(GameObject* object);
	virtual ~MovementComponent();

	void onUpdate(float deltaTime);

	void addVelocity(Vector3 value) noexcept;
	void addForce(Vector3 value) noexcept;

protected:
	Vector3 force;
	float mass = 100.f;
	Vector3 position = Vector3::zero;
	Vector3 acceleration, velocity;
	Transform* mTransform;
};


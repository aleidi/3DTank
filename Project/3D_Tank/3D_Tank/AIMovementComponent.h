#pragma once
#include "MovementComponent.h"

class AIMovementComponent : public MovementComponent
{
public:
	AIMovementComponent(GameObject* object);
	~AIMovementComponent();

	void onUpdate(float deltaTime);
	void addVelocity(Vector3 value);
	void addForce(Vector3 value);

protected:
	Vector3 force;
	float mass;
	Vector3 position;
	Vector3 acceleration, velocity;
};
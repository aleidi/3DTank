#include "AIMovementComponent.h"


AIMovementComponent::AIMovementComponent(GameObject* object) : MovementComponent(object)
{
	mass = 100.f;
	position = Vector3::zero;
}

AIMovementComponent::~AIMovementComponent()
{
}

void AIMovementComponent::onUpdate(float deltaTime)
{
	/*
	float dot = 0.0f, angle = 0.0f;

	acceleration = force / mass;
	if (!(force == Vector3::zero))
	{
		dot = Vector3::dot(force.normalize(), mTransform->Forward.normalize());
		angle = acos(dot);
		mTransform->rotateY(angle);
	}

	Vector3 tempVelocity = velocity + acceleration * deltaTime;
	if (Vector3::lengthSq(velocity, Vector3(0, 0, 0)) <= 0.0001)
		velocity += acceleration * deltaTime;
	position += velocity * deltaTime;
	mTransform->translate(position);
	*/
}

void AIMovementComponent::addVelocity(Vector3 value)
{
	mTransform->translate(value);
}

void AIMovementComponent::addForce(Vector3 value)
{
	force = value;
}

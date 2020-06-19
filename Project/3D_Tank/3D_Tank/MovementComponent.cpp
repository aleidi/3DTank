#include "MovementComponent.h"
#include "GameObject.h"
#include <cmath>

MovementComponent::MovementComponent(GameObject * object)
	:Component(object)
{
	mTransform = object->getTransform();
}

MovementComponent::~MovementComponent()
{

}

void MovementComponent::onUpdate(float deltaTime)
{
	float dot, angle;

	acceleration = force / mass;
	if (!(force == Vector3::zero))
	{
		dot = Vector3::dot(force.normalize(), mTransform->Forward.normalize());
		angle = acos(dot);
		mTransform->rotateY(angle);
	}

	Vector3 tempVelocity = velocity + acceleration * deltaTime;
	if (tempVelocity.z <= 0.001)
		velocity += acceleration * deltaTime;
	position += velocity * deltaTime;
	mTransform->translate(position);
}

void MovementComponent::addVelocity(Vector3 value) noexcept
{
	mTransform->translate(value);
}

void MovementComponent::addForce(Vector3 value) noexcept
{
	force = value;
}

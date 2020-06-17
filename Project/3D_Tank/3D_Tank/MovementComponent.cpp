#include "MovementComponent.h"
#include "GameObject.h"

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
	Vector3 force, acceleration, velocity, position;
	float mass = 1.0f;

	acceleration = force / mass;
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
}

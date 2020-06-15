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

void MovementComponent::addVelocity(Vector3 value) noexcept
{
	mTransform->translate(value);
}

void MovementComponent::addForce(Vector3 value) noexcept
{
}

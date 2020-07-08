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

void MovementComponent::onUpdate(const float& deltaTime)
{
	
}



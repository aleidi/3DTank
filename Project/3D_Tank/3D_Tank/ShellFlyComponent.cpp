#include "ShellFlyComponent.h"
#include "GameObject.h"
#include "Transform.h"

ShellFlyComponent::ShellFlyComponent(GameObject * obj):Component(obj)
{
	this->velocity = this->getObject()->getTransform()->Forward;
	this->gracity = Vector3(0.f, -0.05f, 0.f);
}

ShellFlyComponent::~ShellFlyComponent()
{
}

void ShellFlyComponent::onUpdate(float detaTime)
{
	this->getObject()->getTransform()->translate(velocity * detaTime);
	velocity.x += gracity.x * detaTime;
	velocity.y += gracity.y * detaTime;
	velocity.z += gracity.z * detaTime;
}

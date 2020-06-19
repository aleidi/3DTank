#include "ShellFlyComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoundingSphere.h"

ShellFlyComponent::ShellFlyComponent(GameObject * obj):Component(obj)
{
	this->velocity = this->getObject()->getTransform()->Forward;
	this->gracity = Vector3(0.f, 0.f, 0.f);
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
	if (this->getObject()->sphere && this->getObject()->sphere->moveable == 1) {
		this->getObject()->sphere->sphere.Center.x += velocity.x*detaTime;
		this->getObject()->sphere->sphere.Center.y += velocity.y*detaTime;
		this->getObject()->sphere->sphere.Center.z += velocity.z*detaTime;
	}
}

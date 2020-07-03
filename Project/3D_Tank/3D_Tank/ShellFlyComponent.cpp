#include "ShellFlyComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoundingSphere.h"
#include "Math.h"

ShellFlyComponent::ShellFlyComponent(GameObject * obj):Component(obj)
{
	this->velocity = this->getObject()->getTransform()->Forward.normalize() * 5.f;
	this->gracity = Vector3(0.f, 0.f, 0.f);
	this->rotateSpeed = 90.f;
	angle = 0.f;
}

ShellFlyComponent::ShellFlyComponent(GameObject * obj, const Vector3 & direction) :Component(obj)
{
	this->velocity = direction.normalize() * 5.f;
	this->gracity = Vector3(0.f, 0.f, 0.f);
	this->rotateSpeed = 90.f;
	angle = 0.f;
}

ShellFlyComponent::~ShellFlyComponent()
{
	if (target) {
		target->destroy();
	}
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
	if (target) {
		updateForward(detaTime);
		this->velocity = this->getObject()->getTransform()->Forward.normalize() * 5.f;
	}
}

void ShellFlyComponent::updateForward(float detaTime)
{
	finalForward = (target->getTransform()->getPosition() - this->getObject()->getTransform()->getPosition()).normalize();
	DirectX::XMFLOAT3 f1(this->getObject()->getTransform()->Forward.x, this->getObject()->getTransform()->Forward.y, this->getObject()->getTransform()->Forward.z);
	DirectX::XMFLOAT3 f2(finalForward.x, finalForward.y, finalForward.z);
	DirectX::XMVECTOR for1 = DirectX::XMLoadFloat3(&f1);
	DirectX::XMVECTOR for2 = DirectX::XMLoadFloat3(&f2);
	angle = DirectX::XMConvertToDegrees(DirectX::XMVectorGetX(DirectX::XMVector3AngleBetweenVectors(for1, for2)));
	if (finalForward != this->getObject()->getTransform()->Forward.normalize()) {
		this->getObject()->getTransform()->Forward = Math::lerp(this->getObject()->getTransform()->Forward, finalForward, angle / rotateSpeed).normalize();
	}
}

void ShellFlyComponent::setTarget(GameObject* t)
{
	this->target = t;
}

void ShellFlyComponent::setVelocity(const Vector3 & dir)
{
	this->velocity = dir.normalize() * 5.f;
}

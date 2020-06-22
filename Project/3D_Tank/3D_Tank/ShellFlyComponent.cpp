#include "ShellFlyComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoundingSphere.h"
#include "Math.h"

ShellFlyComponent::ShellFlyComponent(GameObject * obj):Component(obj)
{
	this->velocity = this->getObject()->getTransform()->Forward.normalize();
	this->gracity = Vector3(0.f, 0.f, 0.f);
	this->rotateSpeed = 90;
	angle = 0.f;
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
	updateForward(detaTime);
	this->velocity = this->getObject()->getTransform()->Forward.normalize() * 5.f;
}

void ShellFlyComponent::updateForward(float detaTime)
{
	finalForward = (target->getTransform()->getPosition() - this->getObject()->getTransform()->getPosition()).normalize();
	DirectX::XMFLOAT3 f1(this->getObject()->getTransform()->Forward.x, this->getObject()->getTransform()->Forward.y, this->getObject()->getTransform()->Forward.z);
	DirectX::XMFLOAT3 f2(finalForward.x, finalForward.y, finalForward.z);
	DirectX::XMVECTOR for1 = DirectX::XMLoadFloat3(&f1);
	DirectX::XMVECTOR for2 = DirectX::XMLoadFloat3(&f2);
	angle = DirectX::XMConvertToDegrees(DirectX::XMVectorGetX(DirectX::XMVector3AngleBetweenVectors(for1, for2)));
	//if (angle != 0.f) {
	//	this->getObject()->getTransform()->Forward = Math::lerp(this->getObject()->getTransform()->Forward, finalForward, 10.f*detaTime).normalize();
	//}
	if (finalForward != this->getObject()->getTransform()->Forward.normalize()) {
		DirectX::XMFLOAT3 shellF;
		shellF.x = this->getObject()->getTransform()->Forward.x;
		shellF.y = this->getObject()->getTransform()->Forward.y;
		shellF.z = this->getObject()->getTransform()->Forward.z;
		DirectX::XMVECTOR shellForward = DirectX::XMLoadFloat3(&shellF);
		DirectX::XMFLOAT3 finalF;
		finalF.x = finalForward.x; finalF.y = finalForward.y; finalF.z = finalForward.z;
		DirectX::XMVECTOR finalXMVector = DirectX::XMLoadFloat3(&finalF);
		DirectX::XMVECTOR lerpForward = DirectX::XMVectorLerp(shellForward, finalXMVector, angle / rotateSpeed);
		DirectX::XMFLOAT3 lerpVector3;
		DirectX::XMStoreFloat3(&lerpVector3,lerpForward);
		this->getObject()->getTransform()->Forward.x = lerpVector3.x;
		this->getObject()->getTransform()->Forward.y = lerpVector3.y;
		this->getObject()->getTransform()->Forward.z = lerpVector3.z;
		this->getObject()->getTransform()->Forward.normalize();
	}
}

void ShellFlyComponent::setTarget(GameObject* t)
{
	if (t) {
		this->target = t;
	}
}

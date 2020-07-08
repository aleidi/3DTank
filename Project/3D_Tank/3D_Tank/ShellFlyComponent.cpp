#include "ShellFlyComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoundingSphere.h"
#include "Math.h"
#include "SceneManager.h"
#include "ParticleSystem.h"
#include "Engine.h"

ShellFlyComponent::ShellFlyComponent(GameObject * obj):Component(obj)
{
	this->velocity = this->getObject()->getTransform()->Forward.normalize();
	this->gracity = Vector3(0.f, 0.f, 0.f);
	this->rotateSpeed = 90.f;
	angle = 0.f;
	count = 0.f;
}

ShellFlyComponent::ShellFlyComponent(GameObject * obj, const Vector3 & direction) :Component(obj)
{
	this->velocity = direction.normalize();
	this->gracity = Vector3(0.f, 0.f, 0.f);
	this->rotateSpeed = 90.f;
	angle = 0.f;
	count = 0.f;
	initParticle();
}

ShellFlyComponent::~ShellFlyComponent()
{
	if (mPS != nullptr)
	{
		mPS->stop();
		SceneManager::sGetInstance()->removeParticleFromPool(mPS);
		mPS = nullptr;
	}
	target = nullptr;
}

void ShellFlyComponent::onUpdate(const float& detaTime)
{
	if (this->getObject()->getTransform()->getPosition() == Vector3(0.f,-3.f,0.f))
		return;
	else {
		if (target) {
			this->getObject()->getTransform()->translate(velocity * detaTime * 2.f);
			velocity.x += gracity.x * detaTime;
			velocity.y += gracity.y * detaTime;
			velocity.z += gracity.z * detaTime;
			if (this->getObject()->sphere && this->getObject()->sphere->moveable == 1) {
				this->getObject()->sphere->sphere.Center.x += velocity.x*detaTime * 2.f;
				this->getObject()->sphere->sphere.Center.y += velocity.y*detaTime * 2.f;
				this->getObject()->sphere->sphere.Center.z += velocity.z*detaTime * 2.f;
			}
			count += detaTime;
			if (target && count >= 1.f) {
				updateForward(detaTime);
				//this->velocity = this->getObject()->getTransform()->Forward.normalize();
				//this->velocity.y = 0.f;
				Vector3 pos = this->getObject()->getTransform()->getPosition();
				mPS->setPosition(pos.x, pos.y, pos.z);
				mPS->play();
				count = 0.f;
			}
		}
		else {
			this->getObject()->getTransform()->translate(velocity * detaTime * 20.f);
			velocity.x += gracity.x * detaTime;
			velocity.y += gracity.y * detaTime;
			velocity.z += gracity.z * detaTime;
			if (this->getObject()->sphere && this->getObject()->sphere->moveable == 1) {
				this->getObject()->sphere->sphere.Center.x += velocity.x*detaTime * 20.f;
				this->getObject()->sphere->sphere.Center.y += velocity.y*detaTime * 20.f;
				this->getObject()->sphere->sphere.Center.z += velocity.z*detaTime * 20.f;
			}
		}
	}
}

void ShellFlyComponent::updateForward(float detaTime)
{
	Vector3 forward = this->velocity.normalize();
	forward.y = 0.f;
	finalForward = (target->getTransform()->getPosition() - this->getObject()->getTransform()->getPosition()).normalize();
	finalForward.y = 0.f;
	float dot = Vector3::dot(finalForward, forward);
	dot = Math::Clamp(1.0f, -1.0f, dot);
	float rotate = acosf(dot) * 180 / Pi;
	Vector3 cross = Vector3::cross(finalForward, forward);
	if (cross.y > 0)
		rotate = -rotate;
	//DirectX::XMFLOAT3 f1(forward.x, forward.y, forward.z);
	//DirectX::XMFLOAT3 f2(finalForward.x, finalForward.y, finalForward.z);
	//DirectX::XMVECTOR for1 = DirectX::XMLoadFloat3(&f1);
	//DirectX::XMVECTOR for2 = DirectX::XMLoadFloat3(&f2);
	//angle = DirectX::XMConvertToDegrees(DirectX::XMVectorGetX(DirectX::XMVector3AngleBetweenVectors(for1, for2)));
	this->getObject()->getTransform()->rotate(0.f, rotate, 0.f);
	this->velocity = finalForward;
	//velocity = this->getObject()->getTransform()->Forward;
	//if (angle == 0.f) return;
	//if (angle <= 20.f && angle != 0.f) {
	//	this->getObject()->getTransform()->Forward = finalForward.normalize();
	//	return;
	//}
	//float dot = Vector3::dot(finalForward, forward);
	//dot = Math::Clamp(1.0f, -1.0f, dot);
	//float rotate = acosf(dot) * 180 / Pi;
	//Vector3 cross = Vector3::cross(finalForward, forward);
	//if (cross.y > 0)
	//	rotate = -rotate;
	//this->getObject()->getTransform()->rotate(0.f, -rotate, 0.f);
	//if (finalForward != this->getObject()->getTransform()->Forward.normalize()) {
	//	this->getObject()->getTransform()->Forward = Math::lerp(this->getObject()->getTransform()->Forward, finalForward, angle / rotateSpeed).normalize();
	//	//float dot = Vector3::dot(this->getObject()->getTransform()->Forward, Math::lerp(this->getObject()->getTransform()->Forward, finalForward, angle / rotateSpeed).normalize());
	//	//dot = Math::Clamp(1.0f, -1.0f, dot);
	//	//float rotate = acosf(dot) * 180 / Pi;
	//	//Vector3 cross = Vector3::cross(this->getObject()->getTransform()->Forward, Math::lerp(this->getObject()->getTransform()->Forward, finalForward, angle / rotateSpeed).normalize());
	//	//if (cross.y > 0)
	//	//	rotate = -rotate;
	//	//this->getObject()->getTransform()->rotate(0.f, -rotate, 0.f);
	//}
}

void ShellFlyComponent::setTarget(GameObject* t)
{
	this->target = t;
}

void ShellFlyComponent::setVelocity(const Vector3 & dir)
{
	if (Vector3::zero == dir) {
		this->velocity = Vector3::zero;
	}
	else {
		this->velocity = dir.normalize();
	}
}

Vector3 ShellFlyComponent::getVelocity()
{
	return velocity;
}

void ShellFlyComponent::initParticle()
{
	mPS = SceneManager::sGetInstance()->createParticleSystem(L"VFX/green_fire_new_1_sheet");
	mPS->setTile(4.0f, 4.0f);
	mPS->setEmitter(ParticleSystem::Emitter::NoEmit);
	mPS->setEmitRate(2.0f);
	mPS->setLifeTime(0.5f);
	mPS->setAnimationInterval(0.5f / 16.0f);
	mPS->setStartScale(0.2f, 0.2f, 0.2f);
}

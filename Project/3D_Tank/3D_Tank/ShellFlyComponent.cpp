#include "ShellFlyComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoundingSphere.h"
#include "Math.h"
#include "SceneManager.h"
#include "ParticleSystem.h"

ShellFlyComponent::ShellFlyComponent(GameObject * obj):Component(obj)
{
	this->velocity = this->getObject()->getTransform()->Forward.normalize() * 20.f;
	this->gracity = Vector3(0.f, 0.f, 0.f);
	this->rotateSpeed = 90.f;
	angle = 0.f;
}

ShellFlyComponent::ShellFlyComponent(GameObject * obj, const Vector3 & direction) :Component(obj)
{
	this->velocity = direction.normalize() * 20.f;
	this->gracity = Vector3(0.f, 0.f, 0.f);
	this->rotateSpeed = 90.f;
	angle = 0.f;
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
}

void ShellFlyComponent::onUpdate(const float& detaTime)
{
	if (this->getObject()->getTransform()->getPosition() == Vector3(0.f,-3.f,0.f))
		return;
	else {
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
			this->velocity = this->getObject()->getTransform()->Forward.normalize() * 20.f;
			Vector3 pos = this->getObject()->getTransform()->getPosition();
			mPS->setPosition(pos.x, pos.y, pos.z);
			mPS->play();
		}
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
	if (Vector3::zero == dir) {
		this->velocity = Vector3::zero;
	}
	else {
		this->velocity = dir.normalize() * 20.f;
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

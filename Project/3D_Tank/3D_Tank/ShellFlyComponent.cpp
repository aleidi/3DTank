#include "ShellFlyComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoundingSphere.h"
#include "Math.h"
#include "SceneManager.h"
#include "ParticleSystem.h"

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
		float normalShellSpeed, trackShellSpeed;
		if (tankType == 0) { normalShellSpeed = 20.f; trackShellSpeed = 2.f; }
		if (tankType == 1) { normalShellSpeed = 10.f; trackShellSpeed = 2.f; }
		if (target) {
			this->getObject()->getTransform()->translate(velocity * detaTime * trackShellSpeed);
			velocity.x += gracity.x * detaTime;
			velocity.y += gracity.y * detaTime;
			velocity.z += gracity.z * detaTime;
			if (this->getObject()->sphere && this->getObject()->sphere->moveable == 1) {
				this->getObject()->sphere->sphere.Center.x += velocity.x*detaTime * trackShellSpeed;
				this->getObject()->sphere->sphere.Center.y += velocity.y*detaTime * trackShellSpeed;
				this->getObject()->sphere->sphere.Center.z += velocity.z*detaTime * trackShellSpeed;
			}
			count += detaTime;
			if (count >= 1.f) {
				updateForward(detaTime);
				Vector3 pos = this->getObject()->getTransform()->getPosition();
				mPS->setPosition(pos.x, pos.y, pos.z);
				mPS->play();
				count = 0.f;
			}
		}
		else {
			this->getObject()->getTransform()->translate(velocity * detaTime * normalShellSpeed);
			velocity.x += gracity.x * detaTime;
			velocity.y += gracity.y * detaTime;
			velocity.z += gracity.z * detaTime;
			if (this->getObject()->sphere && this->getObject()->sphere->moveable == 1) {
				this->getObject()->sphere->sphere.Center.x += velocity.x*detaTime * normalShellSpeed;
				this->getObject()->sphere->sphere.Center.y += velocity.y*detaTime * normalShellSpeed;
				this->getObject()->sphere->sphere.Center.z += velocity.z*detaTime * normalShellSpeed;
			}
		}
	}
}

void ShellFlyComponent::updateForward(float detaTime)
{
	//Vector3 forward = this->velocity.normalize();
	//forward.y = 0.f;
	finalForward = (target->getTransform()->getPosition() - this->getObject()->getTransform()->getPosition()).normalize();
	//finalForward.y = 0.f;
	//Vector3 finalF = finalForward;
	//finalF.y = 0.f;
	//float dot = Vector3::dot(finalF, forward);
	//dot = Math::Clamp(1.0f, -1.0f, dot);
	//float rotate = acosf(dot) * 180 / Pi;
	//Vector3 cross = Vector3::cross(finalF, forward);
	//if (cross.y > 0)
	//	rotate = -rotate;
	//this->getObject()->getTransform()->rotate(0.f, rotate, 0.f);
	this->velocity = finalForward;
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

void ShellFlyComponent::setTankType(const int & type)
{
	tankType = type;
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

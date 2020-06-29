#include "Pawn.h"
#include "MovementComponent.h"
#include "UIHP.h"
#include "Shell.h"

Pawn::Pawn()
{
	mUIHP = new UIHP();
	mUIHP->attach(*this);
	mUIHP->getTransform()->translate(0.0f, 0.4f, 0.0f);
}

Pawn::~Pawn()
{
	mUIHP->destroy();
	mUIHP = nullptr;
}

void Pawn::onStart()
{
	GameObject::onStart();
}

void Pawn::onUpdate(float deltaTime)
{
	GameObject::onUpdate(deltaTime);
}

void Pawn::onLateUpdate(float deltaTime)
{
	mUIHP->onLateUpdate(deltaTime);
}

void Pawn::move(Vector3 value)
{
}

void Pawn::attack(Vector3 batteryposition, Vector3 shot_direction)
{
	Shell* shell = new Shell(batteryposition, shot_direction, 0);
}

void Pawn::onTriggerEnter(const GameObject * obj)
{
}

void Pawn::onCollisionEnter()
{
}

void Pawn::setMaxSpeed(float maxspeed) {
	mAttribute.m_MaxSpeed = maxspeed;
}

float Pawn::getMaxSpeed()const {
	return mAttribute.m_MaxSpeed;
}

void Pawn::setVelocity(Vector3 newVelocity) {
	m_Velocity = newVelocity;
}

Vector3 Pawn::getVelocity()const {
	return m_Velocity;
}
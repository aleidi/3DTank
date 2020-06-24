#include "Pawn.h"
#include "MovementComponent.h"

Pawn::Pawn()
{
	//mMovementComp = new MovementComponent(this);
}

Pawn::~Pawn()
{
}

void Pawn::onStart()
{
	GameObject::onStart();
}

void Pawn::onUpdate(float deltaTime)
{
	GameObject::onUpdate(deltaTime);
}

void Pawn::move(Vector3 value)
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
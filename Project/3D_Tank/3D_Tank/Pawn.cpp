#include "Pawn.h"
#include "MovementComponent.h"
#include "UIHP.h"

Pawn::Pawn()
{
	mUIHP = new UIHP();
	mUIHP->attach(*this);
	mUIHP->getTransform()->translate(0.0f, 0.4f, 0.0f);
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

void Pawn::onLateUpdate(float deltaTime)
{
	mUIHP->onLateUpdate(deltaTime);
}

void Pawn::move(Vector3 value)
{
}

void Pawn::attack(Vector3 direction)
{
}

void Pawn::setVelocity(Vector3 newVelocity) {
	m_Velocity = newVelocity;
}

Vector3 Pawn::getVelocity()const {
	return m_Velocity;
}
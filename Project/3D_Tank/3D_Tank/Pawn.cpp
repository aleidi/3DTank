#include "Pawn.h"
#include "MovementComponent.h"
#include "UIHP.h"
#include "Shell.h"
#include "FileManager.h"
#include "ShellFlyComponent.h"
#include "ShellContainer.h"

Pawn::Pawn()
	:mAttribute{}
{
	mUIHP = new UIHP();
	mUIHP->attach(*this);
	mUIHP->getTransform()->translate(0.0f, 0.4f, 0.0f);
	mUIHP->setEnable(true);
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
	mUIHP->setFillAmount((float)mAttribute.m_HP / (float)mAttribute.FullHP);
	mUIHP->onLateUpdate(deltaTime);
}

void Pawn::move(Vector3 value)
{
}



void Pawn::attack(Vector3 batteryposition, Vector3 shot_direction)
{
	ShellContainer::sGetInstance()->applyShell(batteryposition, shot_direction, 0);
}

void Pawn::attack(Vector3 battery_position, Vector3 shot_direction, Pawn* target)
{
	ShellContainer::sGetInstance()->applyShell(battery_position, shot_direction, 1, target);
}

void Pawn::hited(int value)
{
	mAttribute.m_HP -= value;
}

void Pawn::onTriggerEnter(const GameObject * obj)
{
}

void Pawn::onCollisionEnter()
{
}

void Pawn::addHP(int value)
{
	mAttribute.m_HP += value;
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
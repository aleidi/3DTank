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
	reinterpret_cast<UIHP*>(mUIHP)->setFillAmount((float)mAttribute.m_HP / (float)mAttribute.FullHP);
	mUIHP->onLateUpdate(deltaTime);
}

void Pawn::move(Vector3 value)
{
}



void Pawn::attack(Vector3 batteryposition, Vector3 shot_direction)
{
	//Shell* shell = new Shell(batteryposition, shot_direction, 0);
	if (ShellContainer::sGetInstance()->getUnTriggerShells().size() == 0)
		Shell* shell = new Shell(batteryposition, shot_direction, 0);
	else {
		(*ShellContainer::sGetInstance()->getUnTriggerShells().begin())->resetPosAndDir(batteryposition, shot_direction, 0);
	}
}

void Pawn::attack(Vector3 battery_position, Vector3 shot_direction, Pawn* target)
{
	if (ShellContainer::sGetInstance()->getUnTriggerShells().size() == 0) {
		Shell* shell = new Shell(battery_position, shot_direction, 1);
		shell->getShellComponent()->setTarget(target);
	}
	else {
		(*ShellContainer::sGetInstance()->getUnTriggerShells().begin())->resetPosAndDir(battery_position, shot_direction, 0);
		(*ShellContainer::sGetInstance()->getUnTriggerShells().begin())->getShellComponent()->setTarget(target);
	}
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
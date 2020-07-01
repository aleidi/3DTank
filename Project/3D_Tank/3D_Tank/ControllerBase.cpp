#include "ControllerBase.h"

ControllerBase::ControllerBase(int value)
	: GameObject(-1)
{
}

void ControllerBase::onStart()
{
	GameObject::onStart();
}

void ControllerBase::onUpdate(float deltaTime)
{
	GameObject::onUpdate(deltaTime);
}

void ControllerBase::posses(Pawn * pawn) noexcept
{
	mPawn = pawn;
}

void ControllerBase::unPosses() noexcept
{
	mPawn = nullptr;
}

Pawn * ControllerBase::getPawn() noexcept
{
	return mPawn;
}

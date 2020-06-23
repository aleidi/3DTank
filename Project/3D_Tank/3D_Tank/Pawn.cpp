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

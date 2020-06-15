#include "GameCharacter.h"
#include "MovementComponent.h"

GameCharacter::GameCharacter()
{
}

GameCharacter::~GameCharacter()
{
}

void GameCharacter::onStart()
{
}

void GameCharacter::onUpdate(float deltaTime)
{
}

void GameCharacter::Move(Vector3 value)
{
	mMovementComp->addVelocity(value);
}

#include "GameCharacter.h"
#include "MovementComponent.h"

//test code
#include "SceneManager.h"

GameCharacter::GameCharacter()
{
	//test code
	//movecomp = new MovementComponent(SceneManager::sGetInstance()->findObjectWithName("DefaultPlayer"));
}

GameCharacter::~GameCharacter()
{
}

void GameCharacter::onStart()
{
}

void GameCharacter::onUpdate(const float& deltaTime)
{
}

void GameCharacter::Move(Vector3 value)
{
	mMovementComp->addVelocity(value);
}

MovementComponent* GameCharacter::getMoveComponent()
{
	return movecomp;
}
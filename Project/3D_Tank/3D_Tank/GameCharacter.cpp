#include "GameCharacter.h"
#include "MovementComponent.h"

//テストコード
#include "SceneManager.h"

GameCharacter::GameCharacter()
{
	//テストコード
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
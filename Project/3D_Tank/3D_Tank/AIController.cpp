#include "AIController.h"
#include "GameCharacter.h"

AIController::AIController()
{
}

AIController::~AIController()
{
}

void AIController::onStart()
{
}

void AIController::onUpdate(float deltaTime)
{
	MoveCharacter(Vector3::right * deltaTime);
}

void AIController::MoveCharacter(Vector3 value)
{
	reinterpret_cast<GameCharacter*>(mPawn)->Move(value);
}

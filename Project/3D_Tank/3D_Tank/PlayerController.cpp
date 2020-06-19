#include "PlayerController.h"
#include "PlayerTank.h"
#include "GameCommon.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::onUpdate(float deltaTime)
{
	checkInput(deltaTime);
}

void PlayerController::Move(Vector3 value)
{
	reinterpret_cast<PlayerTank*>(mPawn)->Move(value);
}

void PlayerController::Rotate(float valueX, float valueY)
{
	reinterpret_cast<PlayerTank*>(mPawn)->RotateCamera(valueX, valueY);
	reinterpret_cast<PlayerTank*>(mPawn)->RotateBattery(valueX,valueY);
}

void PlayerController::Attack1()
{
}

void PlayerController::Skill1()
{
}

void PlayerController::checkInput(float deltaTime)
{
	if (DInputPC::getInstance().iskey(MOVEFORWARD))
	{
		Move(mPawn->getTransform()->Forward * deltaTime);
	}
	if (DInputPC::getInstance().iskey(MOVEBACK))
	{
		Move(mPawn->getTransform()->Forward * -deltaTime);
	}
	if (DInputPC::getInstance().iskey(TURNLEFT))
	{
		Move(mPawn->getTransform()->Right * -deltaTime);
	}
	if (DInputPC::getInstance().iskey(TURNRIGHT))
	{
		Move(mPawn->getTransform()->Right * deltaTime);
	}

	Rotate(DInputPC::getInstance().mouseDY() * deltaTime, DInputPC::getInstance().mouseDX() * deltaTime);
}

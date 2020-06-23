#include "PlayerController.h"
#include "PlayerTank.h"
#include "GameCommon.h"

PlayerController::PlayerController()
	:mDisToCamFactor(0.05f), mMirrorMax(XM_PI / 20), mMirrorMin(XM_PI / 3)
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::onUpdate(float deltaTime)
{
	checkInput(deltaTime);
}

void PlayerController::move(Vector3 value)
{
	reinterpret_cast<PlayerTank*>(mPawn)->move(value);
}

void PlayerController::rotate(float value)
{
	reinterpret_cast<PlayerTank*>(mPawn)->rotate(value);
}

void PlayerController::rotateView(float valueX, float valueY)
{
	reinterpret_cast<PlayerTank*>(mPawn)->rotateCamera(valueX, valueY);
}

void PlayerController::adjustDistanceToCam(float value)
{
	reinterpret_cast<PlayerTank*>(mPawn)->adjustDisToCam(value);
}

void PlayerController::setCameraFov(float value)
{
	reinterpret_cast<PlayerTank*>(mPawn)->setCameraFov(value);
}

void PlayerController::checkInput(float deltaTime)
{
	if (DInputPC::getInstance().isMouseButtonDown(MIRROR))
	{
		reinterpret_cast<PlayerTank*>(mPawn)->setCameraFov(mMirrorMax);
	}
	if (DInputPC::getInstance().isMouseButtonUp(MIRROR))
	{
		reinterpret_cast<PlayerTank*>(mPawn)->setCameraFov(mMirrorMin);
	}

	if (DInputPC::getInstance().iskey(MOVEFORWARD))
	{
		move(mPawn->getTransform()->Forward * deltaTime);
	}
	if (DInputPC::getInstance().iskey(MOVEBACK))
	{
		move(mPawn->getTransform()->Forward * -deltaTime);
	}
	if (DInputPC::getInstance().iskey(TURNLEFT))
	{
		rotate(-deltaTime);
	}
	if (DInputPC::getInstance().iskey(TURNRIGHT))
	{
		rotate(deltaTime);
	}

	float dz = DInputPC::getInstance().mouseDZ();
	if (dz > 0)
	{
		adjustDistanceToCam(mDisToCamFactor * -1.0f);
	}
	else if (dz < 0)
	{
		adjustDistanceToCam(mDisToCamFactor);
	}

	rotateView(DInputPC::getInstance().mouseDY() * deltaTime, DInputPC::getInstance().mouseDX() * deltaTime);
}

#include "DefaultPlayerController.h"
#include "GameCommon.h"
#include "DefaultPlayer.h"

DefaultPlayerController::DefaultPlayerController()
	:mRspdX(0.2f),mRspdY(0.1f),mMovSpd(10.0f)
{
	mName = "DefaultPlayerController";
}

DefaultPlayerController::~DefaultPlayerController()
{
}

void DefaultPlayerController::onStart()
{
	ControllerBase::onStart();
}

void DefaultPlayerController::onUpdate(const float& deltaTime)
{
	ControllerBase::onUpdate(deltaTime);

	if (DInputPC::getInstance().iskey(DIK_SPACE))
	{
		return;
	}

	if (DInputPC::getInstance().iskey(MOVEFORWARD))
	{
		reinterpret_cast<DefaultPlayer*>(mPawn)->MoveForward(1.0f * deltaTime * mMovSpd);
	}
	if (DInputPC::getInstance().iskey(MOVEBACK))
	{
		reinterpret_cast<DefaultPlayer*>(mPawn)->MoveForward(-1.0f * deltaTime * mMovSpd);
	}
	if (DInputPC::getInstance().iskey(TURNLEFT))
	{
		reinterpret_cast<DefaultPlayer*>(mPawn)->MoveRight(-1.0f * deltaTime * mMovSpd);
	}
	if (DInputPC::getInstance().iskey(TURNRIGHT))
	{
		reinterpret_cast<DefaultPlayer*>(mPawn)->MoveRight(1.0f * deltaTime * mMovSpd);
	}
	if (DInputPC::getInstance().iskey(DIK_Q))
	{
		reinterpret_cast<DefaultPlayer*>(mPawn)->MoveUp(1.0f * deltaTime * mMovSpd);
	}
	if (DInputPC::getInstance().iskey(DIK_E))
	{
		reinterpret_cast<DefaultPlayer*>(mPawn)->MoveUp(-1.0f * deltaTime * mMovSpd);
	}
	
	reinterpret_cast<DefaultPlayer*>(mPawn)->Rotate(
		DInputPC::getInstance().mouseDY() * mRspdX, DInputPC::getInstance().mouseDX() * mRspdY, 0.0f);
}

#include "DefaultPlayerController.h"
#include "GameCommon.h"
#include "DefaultPlayer.h"

DefaultPlayerController::DefaultPlayerController()
	:mRspdX(0.05f),mRspdY(0.05f),mMovSpd(5.0f)
{
}

DefaultPlayerController::~DefaultPlayerController()
{
}

void DefaultPlayerController::onStart()
{
	ControllerBase::onStart();
}

void DefaultPlayerController::onUpdate(float deltaTime)
{
	ControllerBase::onUpdate(deltaTime);

	if (DInputPC::getInstance().iskey(DIK_W))
	{
		reinterpret_cast<DefaultPlayer*>(mPawn)->MoveForward(1.0f * deltaTime * mMovSpd);
	}
	if (DInputPC::getInstance().iskey(DIK_S))
	{
		reinterpret_cast<DefaultPlayer*>(mPawn)->MoveForward(-1.0f * deltaTime * mMovSpd);
	}
	if (DInputPC::getInstance().iskey(DIK_A))
	{
		reinterpret_cast<DefaultPlayer*>(mPawn)->MoveRight(-1.0f * deltaTime * mMovSpd);
	}
	if (DInputPC::getInstance().iskey(DIK_D))
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

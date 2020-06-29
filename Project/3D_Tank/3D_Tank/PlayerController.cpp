#include "PlayerController.h"
#include "PlayerTank.h"
#include "GameCommon.h"
#include "CollisionManager.h"
#include "Shell.h"

GameObject* obj;

PlayerController::PlayerController()
	:mDisToCamFactor(0.15f), mMirrorMax(XM_PI / 20), mMirrorMin(XM_PI / 3)
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::onUpdate(float deltaTime)
{
	checkInput(deltaTime);
	if (CollisionManager::sGetInstance()->collisionCheck_CubeToCube(reinterpret_cast<PlayerTank*>(mPawn)->cube,&obj) == true) {
		reinterpret_cast<PlayerTank*>(mPawn)->onTriggerEnter(obj);
	}
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
	if (DInputPC::getInstance().isMouseButtonDown(ATTACK))
	{
		reinterpret_cast<PlayerTank*>(mPawn)->attack();
	}
	if (DInputPC::getInstance().isMouseButtonUp(ATTACK))
	{
		reinterpret_cast<PlayerTank*>(mPawn)->stopAttack();
	}

	if (DInputPC::getInstance().isMouseButtonDown(MIRROR))
	{
		reinterpret_cast<PlayerTank*>(mPawn)->setCameraFov(mMirrorMax);
	}
	if (DInputPC::getInstance().isMouseButtonUp(MIRROR))
	{
		reinterpret_cast<PlayerTank*>(mPawn)->setCameraFov(mMirrorMin);
	}
	if (DInputPC::getInstance().isMouseButtonDown(0))
	{
		Shell* shell = new Shell(reinterpret_cast<PlayerTank*>(mPawn)->getBattery()->getTransform()->getPosition(), reinterpret_cast<PlayerTank*>(mPawn)->getBattery()->getTransform()->Forward, 0);
	}

	if (DInputPC::getInstance().iskey(MOVEFORWARD))
	{
		if (reinterpret_cast<PlayerTank*>(mPawn)->onTrigger == false) {
			reinterpret_cast<PlayerTank*>(mPawn)->moveDirection = FORWARD;
			move(mPawn->getTransform()->Forward * deltaTime);
		}
	}
	if (DInputPC::getInstance().iskey(MOVEBACK))
	{
		if (reinterpret_cast<PlayerTank*>(mPawn)->onTrigger == false) {
			reinterpret_cast<PlayerTank*>(mPawn)->moveDirection = (MoveDirection)1;
			move(mPawn->getTransform()->Forward * -deltaTime);
		}
	}
	if (DInputPC::getInstance().iskey(TURNLEFT))
	{
		if (reinterpret_cast<PlayerTank*>(mPawn)->onTrigger == false) {
			reinterpret_cast<PlayerTank*>(mPawn)->moveDirection = LEFT;
			rotate(-deltaTime);
		}
	}
	if (DInputPC::getInstance().iskey(TURNRIGHT))
	{
		if (reinterpret_cast<PlayerTank*>(mPawn)->onTrigger == false) {
			reinterpret_cast<PlayerTank*>(mPawn)->moveDirection = RIGHT;
			rotate(deltaTime);
		}
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
	else
	{
		adjustDistanceToCam(0.0f);
	}

	rotateView(DInputPC::getInstance().mouseDY() * deltaTime, DInputPC::getInstance().mouseDX() * deltaTime);
}

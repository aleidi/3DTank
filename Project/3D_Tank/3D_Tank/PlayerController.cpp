#include "PlayerController.h"
#include "PlayerTank.h"
#include "GameCommon.h"
#include "CollisionManager.h"

PlayerController::PlayerController()
	:mDisToCamFactor(0.15f), mMirrorMax(XM_PI / 20), mMirrorMin(XM_PI / 3)
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::onUpdate(const float& deltaTime)
{
	if (!mIsEnable)
	{
		return;
	}
	checkInput(deltaTime);
	GameObject* obj;
	if (CollisionManager::sGetInstance()->collisionCheck_CubeToCube(reinterpret_cast<PlayerTank*>(mPawn)->cube,&obj) == true) {
		reinterpret_cast<PlayerTank*>(mPawn)->onTriggerEnter(obj);
	}
	else {
		reinterpret_cast<PlayerTank*>(mPawn)->onTriggerExit();
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
		reinterpret_cast<PlayerTank*>(mPawn)->setAttack();
	}
	if (DInputPC::getInstance().isMouseButtonUp(ATTACK))
	{
		reinterpret_cast<PlayerTank*>(mPawn)->stopAttack();
	}
	if (DInputPC::getInstance().isMouseButton(ATTACK))
	{
		reinterpret_cast<PlayerTank*>(mPawn)->onAttack(deltaTime);
	}

	if (DInputPC::getInstance().isMouseButtonDown(MIRROR))
	{
		reinterpret_cast<PlayerTank*>(mPawn)->setCameraFov(mMirrorMax);
		reinterpret_cast<PlayerTank*>(mPawn)->setCameraRotSpd(8.0f);
	}
	if (DInputPC::getInstance().isMouseButtonUp(MIRROR))
	{
		reinterpret_cast<PlayerTank*>(mPawn)->setCameraFov(mMirrorMin);
		reinterpret_cast<PlayerTank*>(mPawn)->setCameraRotSpd(60.0f);
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
			//reinterpret_cast<PlayerTank*>(mPawn)->moveDirection = LEFT;
			reinterpret_cast<PlayerTank*>(mPawn)->rotateDirection = MLEFT;
			rotate(-deltaTime);
			//if (reinterpret_cast<PlayerTank*>(mPawn)->moveDirection == FORWARD)
			//	move(mPawn->getTransform()->Forward * -deltaTime);
			//else if(reinterpret_cast<PlayerTank*>(mPawn)->moveDirection == MBACK)
			//	move(mPawn->getTransform()->Forward * deltaTime);
		}
		else {
			if (reinterpret_cast<PlayerTank*>(mPawn)->moveDirection == FORWARD) {
				if (DInputPC::getInstance().iskey(MOVEBACK))
					move(mPawn->getTransform()->Forward * -deltaTime);
			}
			else {
				if (reinterpret_cast<PlayerTank*>(mPawn)->moveDirection == MBACK) {
					if (DInputPC::getInstance().iskey(MOVEFORWARD))
						move(mPawn->getTransform()->Forward * deltaTime);
				}
			}
		}
	}
	if (DInputPC::getInstance().iskey(TURNRIGHT))
	{
		if (reinterpret_cast<PlayerTank*>(mPawn)->onTrigger == false) {
			//reinterpret_cast<PlayerTank*>(mPawn)->moveDirection = RIGHT;
			reinterpret_cast<PlayerTank*>(mPawn)->rotateDirection = MRIGHT;
			rotate(deltaTime);
			//if (reinterpret_cast<PlayerTank*>(mPawn)->moveDirection == FORWARD)
			//	move(mPawn->getTransform()->Forward * -deltaTime);
			//else if (reinterpret_cast<PlayerTank*>(mPawn)->moveDirection == MBACK)
			//	move(mPawn->getTransform()->Forward * deltaTime);
		}
		else {
			if (reinterpret_cast<PlayerTank*>(mPawn)->moveDirection == FORWARD) {
				if (DInputPC::getInstance().iskey(MOVEBACK))
					move(mPawn->getTransform()->Forward * -deltaTime);
			}
			else {
				if (reinterpret_cast<PlayerTank*>(mPawn)->moveDirection == MBACK) {
					if (DInputPC::getInstance().iskey(MOVEFORWARD))
						move(mPawn->getTransform()->Forward * deltaTime);
				}
			}
		}
	}
	
	if (DInputPC::getInstance().iskeyUp(MOVEFORWARD))
	{
		reinterpret_cast<PlayerTank*>(mPawn)->stopMove();
	}
	if (DInputPC::getInstance().iskeyUp(MOVEBACK))
	{
		reinterpret_cast<PlayerTank*>(mPawn)->stopMove();
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

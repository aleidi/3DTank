#include "TankGamePlay.h"
#include "GameCommon.h"
#include "Transform.h"

TankGamePlay::TankGamePlay(GameObject * object) noexcept
	:ScriptComponent(object)
{
}

void TankGamePlay::onUpdate(float deltaTime)
{
	if (DInputPC::getInstance().iskey(DIK_NUMPAD8))
	{
		if (mTransform->MoveDirection == 1) mTransform->MoveDirection = 0;
		if (mTransform->getObject()->onCollision == false)
			mTransform->translate(mTransform->Forward*deltaTime*3.0f);
	}
	if (DInputPC::getInstance().iskey(DIK_NUMPAD5))
	{
		if (mTransform->MoveDirection == 0) mTransform->MoveDirection = 1;
		if (mTransform->getObject()->onCollision == false)
			mTransform->translate(mTransform->Forward*deltaTime*(-3.0f));
	}
	if (DInputPC::getInstance().iskey(DIK_NUMPAD6))
	{
		if (mTransform->getObject()->onCollision == false)
			mTransform->rotateY(deltaTime*8.0f);
	}
	if (DInputPC::getInstance().iskey(DIK_NUMPAD4))
	{
		if (mTransform->getObject()->onCollision == false)
			mTransform->rotateY(deltaTime*(-8.0f));
	}

}

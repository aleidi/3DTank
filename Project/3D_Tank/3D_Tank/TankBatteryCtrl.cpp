#include "TankBatteryCtrl.h"
#include "GameCommon.h"
#include "Transform.h"

TankBatteryCtrl::TankBatteryCtrl(GameObject * object) noexcept
	:ScriptComponent(object)
{
}

void TankBatteryCtrl::onUpdate(float deltaTime)
{
	if (DInputPC::getInstance().iskey(DIK_NUMPAD9))
	{
		mTransform->rotateY(deltaTime*8.0f);
	}
	if (DInputPC::getInstance().iskey(DIK_NUMPAD7))
	{
		mTransform->rotateY(deltaTime*(-8.0f));
	}
}

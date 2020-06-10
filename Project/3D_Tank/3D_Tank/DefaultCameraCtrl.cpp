#include "DefaultCameraCtrl.h"
#include "GameCommon.h"

DefaultCameraCtrl::DefaultCameraCtrl(GameObject * object) noexcept
	:ScriptComponent(object)
{
}

void DefaultCameraCtrl::onUpdate(float deltaTime)
{
	mTransform->setPosition(mObject->getTransform()->getPosition());
}

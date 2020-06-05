#include "CameraCtrl.h"
#include "GameCommon.h"

CameraCtrl::CameraCtrl(GameObject * object) noexcept
	:ScriptComponent(object)
{
	mTarget = object->find("follow")->getTransform();
}

void CameraCtrl::onUpdate(float deltaTime)
{
	mTransform->setPosition(Math::lerp(mTransform->getPosition(), mTarget->getPosition(), 0.1f*deltaTime*10.0f));
}
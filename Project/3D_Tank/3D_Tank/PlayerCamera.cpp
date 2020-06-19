#include "PlayerCamera.h"
#include "DirectXMath.h"
#include "GameCommon.h"

PlayerCamera::PlayerCamera(GameObject * object)
	:PlayerCamera(object, DirectX::XM_PI / 3, (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.01f, 1000.0f)
{
}

PlayerCamera::PlayerCamera(GameObject * object, float fov, float aspect, float nearZ, float farZ) noexcept
	:Camera(object,fov, aspect, farZ, fov)
{
	MainCamera = this;
}

PlayerCamera::~PlayerCamera()
{
	Position = mObject->getTransform()->getPosition();
	Rotation = mObject->getTransform()->getRotation();
}

void PlayerCamera::onUpdate(float deltaTime)
{
	Position = Math::lerp(Position, mObject->getTransform()->getPosition(), mSpdForPos * deltaTime);
	Rotation = Math::lerp(Rotation, mObject->getTransform()->getRotation(), mSpdForRot * deltaTime);
}

void PlayerCamera::setSpdForPos(float value)
{
	mSpdForPos = value;
}

void PlayerCamera::setSpdForRot(float value)
{
	mSpdForRot = value;
}

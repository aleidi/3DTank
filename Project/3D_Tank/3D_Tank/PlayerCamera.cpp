#include "PlayerCamera.h"
#include "DirectXMath.h"
#include "GameCommon.h"
#include "CollisionManager.h"

#include <sstream>

PlayerCamera::PlayerCamera(GameObject * object)
	:PlayerCamera(object, DirectX::XM_PI / 3, (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.01f, 100.0f)
{
	mCol = new GameObject();
}

PlayerCamera::PlayerCamera(GameObject * object, float fov, float aspect, float nearZ, float farZ) noexcept
	:Camera(object,fov, aspect, nearZ, farZ),
	mTargetFov(fov),mSpdForPos(10.0f),mSpdForRot(10.0f), mSpdForFov(10.0f)
{
	MainCamera = this;
}

PlayerCamera::~PlayerCamera()
{
}

void PlayerCamera::onUpdate(float deltaTime)
{
}

void PlayerCamera::onLateUpdate(float deltaTime)
{
	Position = Math::lerp(Position, mObject->getTransform()->getPosition(), mSpdForPos * deltaTime);
	Rotation = Math::lerp(Rotation, mObject->getTransform()->getRotation(), mSpdForRot * deltaTime);
	Fov = Math::lerp(Fov, mTargetFov, mSpdForFov * deltaTime);

	//raycast test
	Vector3 origin = Position;
	Vector3 dir = Vector3::up * - 1.0f;
	float length = 0.02f;

	float dis = 0.0f;
	if (CollisionManager::sGetInstance()->rayCheckWithObstacle(origin, dir, length, *mCol, dis))
	{
		Position.y = 0.02f;
	}

}

void PlayerCamera::setSpdForPos(float value)
{
	mSpdForPos = value;
}

void PlayerCamera::setSpdForRot(float value)
{
	mSpdForRot = value;
}

void PlayerCamera::setFov(float value)
{
	mTargetFov = value;
}

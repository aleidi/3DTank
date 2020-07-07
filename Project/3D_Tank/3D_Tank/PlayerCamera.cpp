#include "PlayerCamera.h"
#include "DirectXMath.h"
#include "GameCommon.h"
#include "CollisionManager.h"
#include "GameInstance.h"
#include "GameCommon.h"
#include "Engine.h"


PlayerCamera::PlayerCamera(GameObject * object)
	:PlayerCamera(object, DirectX::XM_PI / 3, (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.01f, 1000.0f)
{
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

void PlayerCamera::onUpdate(const float& deltaTime)
{
}

void PlayerCamera::onLateUpdate(const float& deltaTime)
{
	Position = Math::lerp(Position, mObject->getTransform()->getPosition(), mSpdForPos * deltaTime);
	Rotation = Math::lerp(Rotation, mObject->getTransform()->getRotation(), mSpdForRot * deltaTime);
	Fov = Math::lerp(Fov, mTargetFov, mSpdForFov * deltaTime);

	//raycast test
	Vector3 pos = GameInstance::sGetInstance()->getPlayer()->getTransform()->getPosition();
	Vector3 origin = pos;
	Vector3 dir = Position - pos;
	float length = sqrtf(Vector3::dot(dir, dir));
	dir = dir.normalize();
	GameObject* col;
	float dis = 0.0f;

	if (CollisionManager::sGetInstance()->rayCheckWithoutSelf(origin, dir, length, &col, dis,GameInstance::sGetInstance()->getPlayer()))
	{
		if (col->getTag() == GameObject::ObjectTag::Environment)
		{
			Position = pos + dir * dis;
		}
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

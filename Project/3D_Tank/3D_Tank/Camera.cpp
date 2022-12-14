#include "Camera.h"
#include "DirectXMath.h"
#include "GameObject.h"
#include "Transform.h"
#include "GameCommon.h"
#include "RenderCamera.h"

Camera* Camera::MainCamera = nullptr;

Camera::Camera(GameObject * object) noexcept
	:Camera(object, DirectX::XM_PI / 3,(float)WINDOW_WIDTH/WINDOW_HEIGHT,0.01f,1000.0f)
{}

Camera::Camera(GameObject * object, float fov, float aspect, float nearZ, float farZ) noexcept
	:Component(object),
	Fov(fov),Aspect(aspect),Near(nearZ),Far(farZ),targetFov(fov)
{}

Camera::~Camera()
{
	MainCamera = nullptr;
}

void Camera::onUpdate(const float& deltaTime)
{
	Position = mObject->getTransform()->getPosition();
	Rotation = mObject->getTransform()->getRotation();
}

void Camera::setFov(float value)
{
	targetFov = value;
}

void Camera::lockOnTarget(float x, float y, float z)
{
	RenderCamera::setLockTarget(x, y, z);
}

void Camera::unlockTarget()
{
	RenderCamera::unlockTarget();
}

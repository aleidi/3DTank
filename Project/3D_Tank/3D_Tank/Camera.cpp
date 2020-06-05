#include "Camera.h"
#include "DirectXMath.h"
#include "GameObject.h"
#include "Transform.h"

Camera* Camera::MainCamera = nullptr;

Camera::Camera(GameObject * object) noexcept
	:Camera(object, DirectX::XM_PI / 3,(float)WINDOW_WIDTH/WINDOW_HEIGHT,0.01f,1000.0f)
{}

Camera::Camera(GameObject * object, float fov, float aspect, float nearZ, float farZ) noexcept
	:Component(object),
	Fov(fov),Aspect(aspect),Near(nearZ),Far(farZ)
{}

void Camera::onUpdate(float deltaTime)
{
	Position = mObject->getTransform()->getPosition();
	Rotation = mObject->getTransform()->getRotation();
}
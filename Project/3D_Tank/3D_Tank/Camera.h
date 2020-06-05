#pragma once
#include "EngineCommon.h"
#include "Component.h"

class Camera : public Component
{
public:
	Camera(GameObject* object) noexcept;
	Camera(GameObject* object, float fov, float aspect, float nearZ, float farZ) noexcept;

	void onUpdate(float deltaTime) override;
public:
	//frustum
	Vector3 Position;
	Vector3 Rotation;	
	float Fov;
	float Aspect;
	float Near;
	float Far;
	bool IsPerpective;

	static Camera* MainCamera;
};
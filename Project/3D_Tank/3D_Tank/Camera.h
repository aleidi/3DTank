#pragma once
#include "EngineCommon.h"
#include "Component.h"

class Camera : public Component
{
public:
	Camera(GameObject* object) noexcept;
	Camera(GameObject* object, float fov, float aspect, float nearZ, float farZ) noexcept;
	virtual ~Camera();

	void onUpdate(float deltaTime) override;
public:
	Vector3 Position;
	Vector3 Rotation;	
	//frustum
	float Fov;
	float Aspect;
	float Near;
	float Far;
	bool IsPerpective;

	static Camera* MainCamera;
};
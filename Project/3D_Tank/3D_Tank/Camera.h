#pragma once
#include "EngineCommon.h"
#include "Component.h"

class Camera : public Component
{
public:
	Camera(GameObject* object) noexcept;
	Camera(GameObject* object, float fov, float aspect, float nearZ, float farZ) noexcept;
	virtual ~Camera();

	void onUpdate(const float& deltaTime) override;
	virtual void setFov(float value);
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
	static void lockOnTarget(float x, float y, float z);
	static void unlockTarget();
private:
	float targetFov;

};
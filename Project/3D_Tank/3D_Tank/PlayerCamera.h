#pragma once
#include "Camera.h"

class PlayerCamera : public Camera
{
public:
	PlayerCamera(GameObject* object);
	PlayerCamera(GameObject* object, float fov, float aspect, float nearZ, float farZ) noexcept;
	~PlayerCamera();

	void onUpdate(float deltaTime) override;

	void setSpdForPos(float value);
	void setSpdForRot(float value);

private:
	float mTargetFov;
	Vector3 mTargetPosition;
	Vector3 mTargetRotation;

	float mSpdForPos;
	float mSpdForRot;
};


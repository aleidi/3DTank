#pragma once
#include "Camera.h"

class PlayerCamera : public Camera
{
public:
	PlayerCamera(GameObject* object);
	PlayerCamera(GameObject* object, float fov, float aspect, float nearZ, float farZ) noexcept;
	~PlayerCamera();

	void onUpdate(float deltaTime) override;
	void onLateUpdate(float deltaTime) override;

	void setSpdForPos(float value);
	void setSpdForRot(float value);
	void setFov(float value);

private:
	float mTargetFov;

	float mSpdForPos;
	float mSpdForRot;
	float mSpdForFov;

	GameObject* mCol;
};


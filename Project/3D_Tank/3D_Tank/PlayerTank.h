#pragma once
#include "Pawn.h"

class RenderComponent;
class Camera;

class PlayerTank : public Pawn
{
public:
	PlayerTank();
	~PlayerTank();

	void onUpdate(float deltaTime) override;
	void onLateUpdate(float deltaTime) override;

	void move(Vector3 value) override;
	void rotate(float value);
	void rotateCamera(float valueX, float valueY);
	void adjustDisToCam(float value);
	void setCameraFov(float value);

private:
	//tank move and rotate
	float mRotateSpd;
	float mMoveSped;
	float mBatteryRotSpd;
	float mBatteryMaxPitch;
	float mBatteryMinPitch;

	//camera follow paramaters
	float mDisToCam;
	Vector3 mFPCameraOffset;
	float mFPOfssetFactorX;
	float mFPOfssetFactorY;
	float mCamFollowFactorX;
	float mCamFollowFactorY;
	float mMaxPitchAngle;
	float mMinPitchAngle;
	float mFPToTPThreshold;
	float mMinDisToCam;
	float mMaxDisToCam;

	GameObject* mBattery;
	GameObject* mCamFollower;
	GameObject* mCamera;
	Camera* mCameraComp;
};


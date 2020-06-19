#pragma once
#include "Pawn.h"

class RenderComponent;
class Camera;

class PlayerTank : public Pawn
{
public:
	PlayerTank();
	~PlayerTank();

	void Move(Vector3 value) override;
	void RotateBattery(float valueX, float valueY);
	void RotateCamera(float valueX, float valueY);

private:
	Vector3 mAccumulateSpd;
	float mAccumulateRot;
	float mAccumulateRotBX;
	float mAccumulateRotBY;
	float mAccumulateRotCX;
	float mAccumulateRotCY;

	GameObject* mBattery;
	GameObject* mCamFollower;
	Camera* mCamera;
};


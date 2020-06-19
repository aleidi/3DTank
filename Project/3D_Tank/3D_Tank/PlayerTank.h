#pragma once
#include "Pawn.h"

class RenderComponent;

class PlayerTank : public Pawn
{
public:
	PlayerTank();
	~PlayerTank();

	void Move(Vector3 value) override;
	void RotateBattery(float valueX, float valueY);

private:
	Vector3 mAccumulateSpd;
	float mAccumulateRot;
	float mAccumulateRotBX;
	float mAccumulateRotBY;

	GameObject* mBattery;
};


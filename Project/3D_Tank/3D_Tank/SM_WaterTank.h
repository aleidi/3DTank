#pragma once
#include "GameObject.h"

class BoundingCube;

class SM_WaterTank :GameObject {
public:
	SM_WaterTank(const Vector3& position, const Vector3& rotate, const Vector3& scale);
	~SM_WaterTank();

	BoundingCube* getCollisionBox();

private:
	BoundingCube* mCollisionBox;
};
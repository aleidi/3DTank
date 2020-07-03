#pragma once
#include "GameObject.h"

class BoundingCube;

class SM_construction_fence :public GameObject {
public:
	SM_construction_fence(const Vector3& position, const Vector3& rotate, const Vector3& scale);
	~SM_construction_fence();

	BoundingCube* getCollisionBox();

private:
	BoundingCube* mCollisionBox;
};
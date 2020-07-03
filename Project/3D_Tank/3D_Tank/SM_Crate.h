#pragma once
#include "GameObject.h"

class BoundingCube;

class SM_Crate :public GameObject {
public:
	SM_Crate(const Vector3& position, const Vector3& rotate, const Vector3& scale);
	~SM_Crate();

	BoundingCube* getCollisionBox();

private:
	BoundingCube* mCollisionBox;
};
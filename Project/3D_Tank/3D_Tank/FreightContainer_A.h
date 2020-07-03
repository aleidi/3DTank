#pragma once
#include "GameObject.h"

class BoundingCube;

class FreightContainer_A :public GameObject {
public:
	FreightContainer_A(const Vector3& position, const Vector3& rotate, const Vector3& scale, const int& textureNum);
	~FreightContainer_A();

	BoundingCube* getCollisionBox();

private:
	BoundingCube* mCollisionBox;
};
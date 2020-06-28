#pragma once
#include "GameObject.h"

class BoundingCube;

class FreightContainer_A :GameObject {
public:
	FreightContainer_A(const Vector3& position, const Vector3& scale);
	~FreightContainer_A();

	BoundingCube* getCollisionBox();

private:
	BoundingCube* mCollisionBox;
};
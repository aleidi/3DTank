#pragma once
#include "GameObject.h"

class BoundingCube;

class AirWall :public GameObject{
public:
	AirWall(const Vector3& position, const Vector3& scale);
	~AirWall();

	GameObject* airCube;

private:
	BoundingCube* mCollisionBox;
};
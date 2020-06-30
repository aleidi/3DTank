#pragma once
#include "GameObject.h"

class BoundingCube;

class AirWall : GameObject{
public:
	AirWall(const Vector3& position, const Vector3& scale);
	~AirWall();

	GameObject* cube;

private:
	BoundingCube* mCollisionBox;
};
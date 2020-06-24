#pragma once
#include "GameObject.h"

class BoundingCube;

class Ground : GameObject
{
public:
	Ground();
	~Ground();

private:
	BoundingCube* mCollisionBox;
};

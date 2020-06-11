#include "BoundingCube.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Transform.h"


BoundingCube::BoundingCube(GameObject* obj) :Component(obj)
{
}

BoundingCube::~BoundingCube() {
}

void BoundingCube::createBoundingCube(const Vector3 & center, const Vector3 & extents, int isMoveable)
{
	this->center = center;
	this->extents = extents;
	if (CollisionManager::sGetInstance())
	{
		CollisionManager::sGetInstance()->mBoundingCube.push_back(this);
		if (isMoveable == 1) CollisionManager::sGetInstance()->moveableBoundingCube.push_back(this);
	}
}

void BoundingCube::onFixedUpdate(float deltaTime)
{
	this->center = this->getObject()->getTransform()->getPosition();
}
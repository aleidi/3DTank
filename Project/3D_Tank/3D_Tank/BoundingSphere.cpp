#include "BoundingSphere.h"
#include "CollisionManager.h"

BoundingSphere::BoundingSphere(GameObject * obj) :Component(obj)
{
}

BoundingSphere::~BoundingSphere()
{
}

void BoundingSphere::creatBoundingSphere(const Vector3 & cen, const float & r, CollisionManager * manager)
{
	this->center = cen;
	this->radius = r;
	if (manager) manager->mBoundingSphere.push_back(this);
}

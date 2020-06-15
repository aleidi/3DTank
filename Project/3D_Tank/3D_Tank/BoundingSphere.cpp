#include "BoundingSphere.h"
#include "CollisionManager.h"
#include "BoundingCube.h"

MBoundingSphere::MBoundingSphere(GameObject * obj) :Component(obj)
{
}

MBoundingSphere::~MBoundingSphere()
{
}

void MBoundingSphere::creatBoundingSphere(const DirectX::XMVECTOR & max, const DirectX::XMVECTOR & min, CollisionManager * manager)
{
	DirectX::BoundingBox box;
	box.DirectX::BoundingBox::CreateFromPoints(box, max, min);
	DirectX::BoundingSphere::CreateFromBoundingBox(sphere, box);
	if (manager) manager->mBoundingSphere.push_back(this);
}

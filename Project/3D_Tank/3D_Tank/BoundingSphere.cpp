#include "BoundingSphere.h"
#include "CollisionManager.h"
#include "BoundingCube.h"

MBoundingSphere::MBoundingSphere(GameObject * obj) :Component(obj)
{
	this->sphere.Center = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	this->sphere.Radius = 1.f;
}

MBoundingSphere::~MBoundingSphere()
{
}

void MBoundingSphere::creatBoundingSphere(const DirectX::XMVECTOR & max, const DirectX::XMVECTOR & min)
{
	DirectX::BoundingBox box;
	box.DirectX::BoundingBox::CreateFromPoints(box, max, min);
	DirectX::BoundingSphere::CreateFromBoundingBox(sphere, box);
	if (CollisionManager::sGetInstance())
		CollisionManager::sGetInstance()->mBoundingSphere.push_back(this);
}

void MBoundingSphere::createBoundingSphere(const Vector3 & cen, const float & r)
{
	DirectX::XMFLOAT3 center;
	center.x = cen.x; center.y = cen.y; center.z = cen.z;
	this->sphere.Center = center;
	this->sphere.Radius = r;
	if (CollisionManager::sGetInstance())
		CollisionManager::sGetInstance()->mBoundingSphere.push_back(this);
}


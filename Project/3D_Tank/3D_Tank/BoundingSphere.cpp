#include "BoundingSphere.h"
#include "CollisionManager.h"
#include "GameObject.h"
//#include "Transform.h"
//#include "BoundingCube.h"

MBoundingSphere::MBoundingSphere(GameObject * obj) :Component(obj)
{
	this->sphere.Center = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	this->sphere.Radius = 1.f;
	moveable = 0;
	onTrigger = false;
}

MBoundingSphere::~MBoundingSphere()
{
	CollisionManager::sGetInstance()->deleteBoundingSphere(this);
}

void MBoundingSphere::createBoundingSphere(const DirectX::XMVECTOR & max, const DirectX::XMVECTOR & min, const int& isMoveable)
{
	DirectX::BoundingBox box;
	box.DirectX::BoundingBox::CreateFromPoints(box, max, min);
	DirectX::BoundingSphere::CreateFromBoundingBox(sphere, box);
	if (CollisionManager::sGetInstance() && isMoveable != -1)
	{
		if (isMoveable == 0) {
			CollisionManager::sGetInstance()->unmoveableBoundingSphere.push_back(this);
		}
		else {
			CollisionManager::sGetInstance()->moveableBoundingSphere.push_back(this);
		}
		CollisionManager::sGetInstance()->mBoundingSphere.push_back(this);
		this->moveable = isMoveable;
	}
}

void MBoundingSphere::createBoundingSphere(const Vector3 & cen, const float & r, const int& isMoveable)
{
	DirectX::XMFLOAT3 center;
	center.x = cen.x; center.y = cen.y; center.z = cen.z;
	this->sphere.Center = center;
	this->sphere.Radius = r;
	if (CollisionManager::sGetInstance() && isMoveable != -1)
	{
		if (isMoveable == 0) {
			CollisionManager::sGetInstance()->unmoveableBoundingSphere.push_back(this);
		}
		else {
			CollisionManager::sGetInstance()->moveableBoundingSphere.push_back(this);
		}
		CollisionManager::sGetInstance()->mBoundingSphere.push_back(this);
		this->moveable = isMoveable;
	}
}



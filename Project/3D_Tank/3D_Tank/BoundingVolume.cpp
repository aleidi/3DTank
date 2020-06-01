#include "BoundingVolume.h"

BoundingVolume::BoundingVolume(const Vector3& center, const Vector3& extents) {
	DirectX::XMFLOAT3 cen{ center.x,center.y,center.z };
	DirectX::XMFLOAT3 ext{ extents.x, extents.y, extents.z };
	if (AABB == NULL) {
		AABB = new DirectX::BoundingBox(cen, ext);
	}
	else {
		AABB = NULL;
		AABB = new DirectX::BoundingBox(cen, ext);
	}
}

BoundingVolume::BoundingVolume(const BoundingVolume& bv) :AABB(bv.AABB) {}

BoundingVolume::~BoundingVolume() {
	if (AABB != NULL)
		delete AABB;
	AABB = NULL;
}

void BoundingVolume::createAABB(BoundingVolume& out, const Vector3& pt1, const Vector3& pt2) {
	DirectX::FXMVECTOR position1{ pt1.x,pt1.y,pt1.z };
	DirectX::FXMVECTOR position2{ pt2.x,pt2.y,pt2.z };
	DirectX::BoundingBox::CreateFromPoints(*out.AABB, position1, position2);
}

bool BoundingVolume::isCollision(const BoundingVolume& bv1, const BoundingVolume& bv2) {
	return bv1.AABB->Intersects(*bv2.AABB);
}

bool BoundingVolume::isRayIntersectsBV(const BoundingVolume& bv, Ray& ray, float& dis) {
	DirectX::FXMVECTOR origin{ ray.getOrigin().x,ray.getOrigin().y,ray.getOrigin().z };
	DirectX::FXMVECTOR direction{ ray.getDirection().x,ray.getDirection().y,ray.getDirection().z };
	return AABB->Intersects(origin, direction, dis);
}

//BoundingBox Transform function
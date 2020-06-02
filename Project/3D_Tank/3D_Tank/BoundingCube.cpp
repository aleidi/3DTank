#include "BoundingCube.h"

BoundingCube::BoundingCube(const Vector3& center, const Vector3& extents) {
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

BoundingCube::BoundingCube(const BoundingCube& bv) :AABB(bv.AABB) {}

BoundingCube::~BoundingCube() {
	if (AABB != NULL)
		delete AABB;
	AABB = NULL;
}

void BoundingCube::createAABB(BoundingCube& out, const Vector3& pt1, const Vector3& pt2) {
	DirectX::FXMVECTOR position1{ pt1.x,pt1.y,pt1.z };
	DirectX::FXMVECTOR position2{ pt2.x,pt2.y,pt2.z };
	DirectX::BoundingBox::CreateFromPoints(*out.AABB, position1, position2);
}

bool BoundingCube::isCollision(const BoundingCube& bv1, const BoundingCube& bv2) {
	return bv1.AABB->Intersects(*bv2.AABB);
}

bool BoundingCube::isRayIntersectsBV(const BoundingCube& bv, Ray& ray, float& dis) {
	DirectX::FXMVECTOR origin{ ray.getOrigin().x,ray.getOrigin().y,ray.getOrigin().z };
	DirectX::FXMVECTOR direction{ ray.getDirection().x,ray.getDirection().y,ray.getDirection().z };
	return AABB->Intersects(origin, direction, dis);
}

//BoundingBox Transform function
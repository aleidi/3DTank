#include "BoundingCube.h"
#include "Ray.h"
#include "BoundingSphere.h"

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
	if (AABB != NULL) {
		delete AABB;
		AABB = NULL;
	}
}

void BoundingCube::createAABB(BoundingCube& out, const Vector3& pt1, const Vector3& pt2) {
	DirectX::FXMVECTOR position1{ pt1.x,pt1.y,pt1.z };
	DirectX::FXMVECTOR position2{ pt2.x,pt2.y,pt2.z };
	DirectX::BoundingBox::CreateFromPoints(*out.AABB, position1, position2);
}

void BoundingCube::createMerged(const BoundingCube& b1, const BoundingCube& b2) {
	this->AABB->CreateMerged(*this->AABB, *b1.AABB, *b2.AABB);
}

bool BoundingCube::isCollision(const BoundingCube& bv) {
	return this->AABB->Intersects(*bv.AABB);
}

bool BoundingCube::isIntersectRay(Ray* ray, float& dis) {
	DirectX::FXMVECTOR origin{ ray->getOrigin().x,ray->getOrigin().y,ray->getOrigin().z };
	DirectX::FXMVECTOR direction{ ray->getDirection().x,ray->getDirection().y,ray->getDirection().z };
	return this->AABB->Intersects(origin, direction, dis);
}

bool BoundingCube::isIntersectSphere(BoundingSphere* s) {
	return this->AABB->Intersects(s->getSphere());
}

Vector3 BoundingCube::getCenter() {
	return Vector3(this->AABB->Center.x, this->AABB->Center.y, this->AABB->Center.z);
}

void BoundingCube::transform(BoundingCube& out, const float& scale, const Vector3& r, const Vector3& t) {
	DirectX::FXMVECTOR rotation{ r.x,r.y,r.z };
	DirectX::FXMVECTOR translation{ t.x,t.y,t.z };
	out.AABB->Transform(*out.AABB, scale, rotation, translation);
}
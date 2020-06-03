#include "BoundingSphere.h"
#include "Ray.h"

MBoundingSphere::MBoundingSphere() {
	gameSphere = new DirectX::BoundingSphere();
}

MBoundingSphere::MBoundingSphere(const Vector3& c, const float& r) {
	DirectX::XMFLOAT3 center{ c.x,c.y,c.z };
	gameSphere = new DirectX::BoundingSphere(center, r);
}

MBoundingSphere::MBoundingSphere(const MBoundingSphere& other) :gameSphere(other.gameSphere) {
}

MBoundingSphere::~MBoundingSphere() {
	if (gameSphere != NULL) {
		delete gameSphere;
		gameSphere = NULL;
	}
}

void MBoundingSphere::transform(MBoundingSphere& out, const float& scale, const Vector3& r, const Vector3& t) {
	DirectX::FXMVECTOR rotation{ r.x,r.y,r.z };
	DirectX::FXMVECTOR translation{ t.x,t.y,t.z };
	this->gameSphere->Transform(*this->gameSphere, scale, rotation, translation);
}

Vector3 MBoundingSphere::getCenter() {
	return Vector3(this->gameSphere->Center.x, this->gameSphere->Center.y, this->gameSphere->Center.z);
}

DirectX::BoundingSphere MBoundingSphere::getSphere() {
	return *this->gameSphere;
}

bool MBoundingSphere::Collision(const MBoundingSphere& bs) {
	return this->gameSphere->Intersects(*bs.gameSphere);
}

bool MBoundingSphere::isIntersectRay(Ray* ray, float& dis) {
	DirectX::FXMVECTOR origin{ ray->getOrigin().x,ray->getOrigin().y,ray->getOrigin().z };
	DirectX::FXMVECTOR direction{ ray->getDirection().x,ray->getDirection().y,ray->getDirection().z };
	return this->gameSphere->Intersects(origin, direction, dis);
}
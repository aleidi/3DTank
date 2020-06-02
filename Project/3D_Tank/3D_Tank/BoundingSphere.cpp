#include "BoundingSphere.h"

BoundingSphere::BoundingSphere() {
	gameSphere = new DirectX::BoundingSphere();
}

BoundingSphere::BoundingSphere(const Vector3& c, const float& r) {
	DirectX::XMFLOAT3 center{ c.x,c.y,c.z };
	gameSphere = new DirectX::BoundingSphere(center, r);
}

BoundingSphere::~BoundingSphere() {
	if (gameSphere != NULL) {
		delete gameSphere;
		gameSphere = NULL;
	}
}

void BoundingSphere::transform(BoundingSphere& out, const float& scale, const Vector3& r, const Vector3& t) {
	DirectX::FXMVECTOR rotation{ r.x,r.y,r.z };
	DirectX::FXMVECTOR translation{ t.x,t.y,t.z };
	this->gameSphere->Transform(*this->gameSphere, scale, rotation, translation);
}

Vector3 BoundingSphere::getCenter() {
	return Vector3(this->gameSphere->Center.x, this->gameSphere->Center.y, this->gameSphere->Center.z);
}

DirectX::BoundingSphere BoundingSphere::getSphere() {
	return *this->gameSphere;
}
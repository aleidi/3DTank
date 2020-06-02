#pragma once
#include "DirectXCollision.h"
#include "Vector3.h"

class BoundingSphere {
public:
	BoundingSphere();
	BoundingSphere(const Vector3&, const float&);
	BoundingSphere(const BoundingSphere&);
	~BoundingSphere();

	void transform(BoundingSphere&, const float&, const Vector3&, const Vector3&);
	Vector3 getCenter();
	DirectX::BoundingSphere getSphere();

private:
	DirectX::BoundingSphere* gameSphere;

};
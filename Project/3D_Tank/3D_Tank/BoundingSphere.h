#pragma once
#include "DirectXCollision.h"
#include "Vector3.h"

class Ray;

class MBoundingSphere {
public:
	MBoundingSphere();
	MBoundingSphere(const Vector3&, const float&);
	MBoundingSphere(const MBoundingSphere&);
	~MBoundingSphere();

	void transform(MBoundingSphere&, const float&, const Vector3&, const Vector3&);
	Vector3 getCenter();
	DirectX::BoundingSphere getSphere();
	bool Collision(const MBoundingSphere&);
	bool isIntersectRay(Ray*, float&);

private:
	DirectX::BoundingSphere* gameSphere;

};
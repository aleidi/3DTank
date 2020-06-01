#pragma once
#include "Vector3.h"


class Ray {
public:
	Ray();
	Ray(const Vector3& ori, const Vector3& dir);
	Ray(const Ray&);
	~Ray();

	Vector3 getOrigin();
	Vector3 getDirection();

private:
	Vector3 origin;
	Vector3 direction;
};
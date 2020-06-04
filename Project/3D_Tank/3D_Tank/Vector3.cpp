#include<math.h>
#include "Vector3.h"

Vector3 Vector3::up(0.0f, 1.0f, 0.0f);
Vector3 Vector3::right(1.0f, 0.0f, 0.0f);
Vector3 Vector3::forward(0.0f, 0.0f, 1.0f);
Vector3 Vector3::zero(0.0f, 0.0f, 0.0f);
Vector3 Vector3::one(1.0f, 1.0f, 1.0f);

Vector3& Vector3::operator=(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vector3& Vector3::operator += (const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3 Vector3::operator*(float d) const
{
	return Vector3(x*d, y*d, z*d);
}

Vector3 Vector3::normalize() const
{
	float magSq = x * x + y * y + z * z;
	Vector3 value(x, y, z);
	if (magSq > 0.0f)
	{
		float oneOverMag = (float)(1.0f / sqrt(magSq));
		value.x *= oneOverMag;
		value.y *= oneOverMag;
		value.z *= oneOverMag;
	}
	return value;
}

float Vector3::dot(const Vector3& lhs, const Vector3& rhs)
{
	return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

Vector3 Vector3::cross(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(
		lhs.y*rhs.z - lhs.z*rhs.y,
		lhs.z*rhs.x - lhs.x*rhs.z,
		lhs.x*rhs.y - lhs.y*rhs.x
	);
}

Vector3 Vector3::multiply(const Vector3 & lhs, const Vector3 & rhs)
{
	Vector3 v;
	v.x = lhs.x * rhs.x;
	v.y = lhs.y * rhs.y;
	v.z = lhs.z * rhs.z;
	return v;
}

Vector3 operator+(Vector3 lhs, const Vector3 & rhs)
{
	lhs += rhs;
	return lhs;
}

#pragma once
class Vector3
{
public:
	float x = 0, y = 0, z = 0;
	static Vector3 up;
	static Vector3 right;
	static Vector3 forward;
	static Vector3 zero;
	static Vector3 one;

	Vector3() {}
	Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
	Vector3(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {}

	Vector3& operator = (const Vector3&);
	Vector3& operator += (const Vector3&);
	bool operator==(const Vector3&);
	friend Vector3 operator+(Vector3, const Vector3&);
	Vector3 operator * (float) const;
	Vector3 normalize() const;
	static float dot(const Vector3& lhs, const Vector3& rhs);
	static Vector3 cross(const Vector3& lhs, const Vector3& rhs);
	static Vector3 multiply(const Vector3& lhs, const Vector3& rhs);
};

﻿#pragma once
#include "DirectXCollision.h"
#include "Vector3.h"

class Ray;
class MBoundingSphere;

class BoundingCube {
public:
	BoundingCube() { AABB = new DirectX::BoundingBox(); }
	BoundingCube(const Vector3& center, const Vector3& extents);
	BoundingCube(const BoundingCube&);
	~BoundingCube();

	void createAABB(BoundingCube& out, const Vector3& pt1, const Vector3& pt2); //pt1和pt2可以是包围盒某一对角线上的两个顶点，也可以是所有点中xyz分量中最大值和最小值的两个构造点
	void createMerged(const BoundingCube&, const BoundingCube&);
	bool isCollision(const BoundingCube&);
	bool isIntersectRay(Ray*, float&);
	bool isIntersectSphere(MBoundingSphere*);
	Vector3 getCenter();
	void transform(BoundingCube&, const float&, const Vector3&, const Vector3&);

private:
	DirectX::BoundingBox* AABB;
};

//struct XMFLOAT3
//{
//	float x;
//	float y;
//	float z;
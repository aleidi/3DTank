#pragma once
#include "DirectXCollision.h"
#include "Vector3.h"
#include "Ray.h"

class BoundingVolume {
public:
	BoundingVolume() { AABB = new DirectX::BoundingBox(); }
	BoundingVolume(const Vector3& center, const Vector3& extents);
	BoundingVolume(const BoundingVolume&);
	~BoundingVolume();
	//BoundingVolume(const Vector3& center, const Vector3& extents, const Vector3* orientation);

	void createAABB(BoundingVolume& out, const Vector3& pt1, const Vector3& pt2); //pt1和pt2可以是包围盒某一对角线上的两个顶点，也可以是所有点中xyz分量中最大值和最小值的两个构造点
	bool isCollision(const BoundingVolume&, const BoundingVolume&);
	bool isRayIntersectsBV(const BoundingVolume&, Ray&, float&);

private:
	DirectX::BoundingBox* AABB;
	//BoundingOrientedBox* OBB;

};
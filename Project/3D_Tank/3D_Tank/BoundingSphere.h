#pragma once
#include "Vector3.h"
#include "Component.h"

class CollisionManager;

class BoundingSphere : public Component {
public:
	BoundingSphere(GameObject* obj);
	~BoundingSphere();

	void creatBoundingSphere(const Vector3& cen, const float& r, CollisionManager*);

public:
	Vector3 center;
	float radius;

private:

};
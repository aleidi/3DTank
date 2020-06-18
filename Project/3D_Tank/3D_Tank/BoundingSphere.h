#pragma once
#include "Vector3.h"
#include "Component.h"
#include "DirectXCollision.h"

class CollisionManager;

class MBoundingSphere : public Component {
public:
	MBoundingSphere(GameObject* obj);
	~MBoundingSphere();

	void createBoundingSphere(const DirectX::XMVECTOR& max, const DirectX::XMVECTOR & min, const int& moveable);
	void createBoundingSphere(const Vector3& cen, const float& r, const int& moveable);

public:
	int moveable;
	bool onTrigger;

	DirectX::BoundingSphere sphere;

private:

};
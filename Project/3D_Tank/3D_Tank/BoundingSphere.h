#pragma once
#include "Vector3.h"
#include "Component.h"
#include "DirectXCollision.h"

class CollisionManager;

class MBoundingSphere : public Component {
public:
	MBoundingSphere(GameObject* obj);
	~MBoundingSphere();

	void creatBoundingSphere(const DirectX::XMVECTOR& max, const DirectX::XMVECTOR & min);
	void createBoundingSphere(const Vector3& cen, const float& r);

public:
	DirectX::BoundingSphere sphere;

private:

};
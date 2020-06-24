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

	//virtual bool onTriggerEnter();
	//virtual bool onTriggerExit();
	//virtual bool onCollisionEnter();
	//virtual bool onCollisionExit();

public:
	int moveable;
	bool onTrigger;
	bool onCollision;

	DirectX::BoundingSphere sphere;

private:

};
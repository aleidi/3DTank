#pragma once
#include "Vector3.h"
#include "Component.h"
#include "DirectXCollision.h"

class CollisionManager;

class BoundingCube : public Component {
public:
	BoundingCube(GameObject* obj);
	~BoundingCube();

	void createBoundingCube(const DirectX::XMVECTOR& center, const DirectX::XMVECTOR& extents, int isMoveable);// pt1とpt2には、バウンディングボックスの対角頂点、または全頂点のXYZ成分の最大値と最小値から構成した点を指定できる
	void createBoundingCube(const Vector3& center, const Vector3& extents, int isMoveable);
	void createBoundingCube(const BoundingCube* cube1, const BoundingCube* cube2);
	void onFixedUpdate(const float& deltaTime) override;
	void translate(const Vector3& translate);

	//virtual bool onTriggerEnter();
	//virtual bool onTriggerExit();
	//virtual bool onCollisionEnter();
	//virtual bool onCollisionExit();

	int moveable;
	bool onTrigger;
	bool onCollision;

	DirectX::BoundingOrientedBox box;
	DirectX::BoundingOrientedBox outBox;
private:

};
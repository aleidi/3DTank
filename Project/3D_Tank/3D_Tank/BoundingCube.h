#pragma once
#include "Vector3.h"
#include "Component.h"
#include "DirectXCollision.h"

class CollisionManager;

class BoundingCube : public Component {
public:
	BoundingCube(GameObject* obj);
	~BoundingCube();

	void createBoundingCube(const DirectX::XMVECTOR& center, const DirectX::XMVECTOR& extents, int isMoveable);//pt1和pt2可以是包围盒某一对角线上的两个顶点，也可以是所有点中xyz分量中最大值和最小值的两个构造点
	//void transform(const float&, const Vector3&, const Vector3&);
	void onFixedUpdate(float deltaTime) override;

	int moveable;
	bool onTrigger;
	DirectX::BoundingOrientedBox box;
	DirectX::BoundingOrientedBox outBox;
private:

};
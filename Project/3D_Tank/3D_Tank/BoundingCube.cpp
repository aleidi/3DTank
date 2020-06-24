#include "BoundingCube.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Transform.h"


BoundingCube::BoundingCube(GameObject* obj) :Component(obj)
{
	box.Center = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	box.Extents = DirectX::XMFLOAT3(1.f, 1.f, 1.f);
	box.Orientation = DirectX::XMFLOAT4(0.f, 0.f, 0.f, 1.f);
	moveable = 0;
}

BoundingCube::~BoundingCube() {
}

void BoundingCube::createBoundingCube(const DirectX::XMVECTOR & maxPoint, const DirectX::XMVECTOR & minPoint, int isMoveable)
{
	DirectX::BoundingBox box1;
	DirectX::BoundingBox::CreateFromPoints(box1, maxPoint, minPoint);
	outBox.Center = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	outBox.Extents = DirectX::XMFLOAT3(1.f, 1.f, 1.f);
	outBox.Orientation = DirectX::XMFLOAT4(0.f, 0.f, 0.f, 1.f);
	DirectX::BoundingOrientedBox::CreateFromBoundingBox(outBox, box1);
	box = outBox;
	if (isMoveable != -1) {
		if (CollisionManager::sGetInstance())
		{
			if (isMoveable == 1) {
				CollisionManager::sGetInstance()->moveableBoundingCube.push_back(this);
			}
			else {
				CollisionManager::sGetInstance()->unmoveableBoundingCube.push_back(this);
			}
			CollisionManager::sGetInstance()->mBoundingCube.push_back(this);
			this->moveable = isMoveable;
		}
	}
}

void BoundingCube::createBoundingCube(const BoundingCube * cube1, const BoundingCube * cube2)
{

}

void BoundingCube::onFixedUpdate(float deltaTime)
{
	//outBox.Center = DirectX::XMFLOAT3(0.f, 0.f, 0.f);
	//outBox.Extents = DirectX::XMFLOAT3(1.f, 1.f, 1.f);
	//outBox.Orientation = DirectX::XMFLOAT4(0.f, 0.f, 0.f, 1.f);
	//this->box.Transform(outBox, this->getObject()->getTransform()->getLocalToWorldMatrix());
	//box = outBox;
}
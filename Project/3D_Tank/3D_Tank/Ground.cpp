#include "Ground.h"
#include "GameCommon.h"

Ground::Ground()
{
	DirectX::XMVECTOR maxPoint, minPoint;
	setName("Ground");
	SceneManager::sGetInstance()->createModel(*this, "Objects\\Ground", L"Objects\\TX_RockyMud_01_ALB", maxPoint, minPoint);
	mTransform->rotateZ(180);

	mCollisionBox = new BoundingCube(this);
	mCollisionBox->createBoundingCube(maxPoint, minPoint, 0);
	addComponent(mCollisionBox);
	DirectX::BoundingOrientedBox out;
	mTransform->calcultateTransformMatrix();
	mCollisionBox->box.Transform(out, mTransform->getLocalToWorldMatrix());
	mCollisionBox->box = out;
	cube = mCollisionBox;
}

Ground::~Ground()
{
}

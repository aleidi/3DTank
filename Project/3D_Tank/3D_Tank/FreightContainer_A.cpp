#include "FreightContainer_A.h"
#include "GameCommon.h"

FreightContainer_A::FreightContainer_A(const Vector3& position, const Vector3& scale)
{
	DirectX::XMVECTOR maxPoint, minPoint;
	setName("Ground");
	SceneManager::sGetInstance()->createModel(*this, "Objects\\SM_FreightContainer_01", L"Objects\\TX_FreightContainer_01a_ALB", maxPoint, minPoint);
	mTransform->translate(position);
	mTransform->setScale(scale);

	mCollisionBox = new BoundingCube(this);
	mCollisionBox->createBoundingCube(maxPoint, minPoint, 0);
	addComponent(mCollisionBox);
	mTransform->calcultateTransformMatrix();
	mCollisionBox->box.Transform(mCollisionBox->box, mTransform->getLocalToWorldMatrix());
}

FreightContainer_A::~FreightContainer_A()
{
}

BoundingCube * FreightContainer_A::getCollisionBox()
{
	return mCollisionBox;
}

#include "SM_Crate.h"
#include "GameCommon.h"

SM_Crate::SM_Crate(const Vector3& position, const Vector3& rotate, const Vector3& scale)
{
	DirectX::XMVECTOR maxPoint, minPoint;
	SceneManager::sGetInstance()->createModel(*this, "Objects\\SM_Crate_01a", L"Objects\\TX_Crates_01a_ALB", maxPoint, minPoint);
	mTransform->setPosition(position);
	mTransform->setScale(scale);

	DirectX::XMFLOAT3 maxP(69.7716980f, 103.348999f, 48.9459991f);
	DirectX::XMFLOAT3 minP(-63.9538002f, 0.000000000f, -39.2224998f);
	maxPoint = DirectX::XMLoadFloat3(&maxP); minPoint = DirectX::XMLoadFloat3(&minP);
	mCollisionBox = new BoundingCube(this);
	mCollisionBox->createBoundingCube(maxPoint, minPoint, 0);
	addComponent(mCollisionBox);
	mTransform->calcultateTransformMatrix();
	DirectX::BoundingOrientedBox out;
	mCollisionBox->box.Transform(out, mTransform->getLocalToWorldMatrix());
	mCollisionBox->box = out;
	this->cube = mCollisionBox;
}

SM_Crate::~SM_Crate()
{
}

BoundingCube * SM_Crate::getCollisionBox()
{
	return mCollisionBox;
}

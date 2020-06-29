#include "SM_construction_fence.h"
#include "GameCommon.h"

SM_construction_fence::SM_construction_fence(const Vector3& position, const Vector3& rotate, const Vector3& scale)
{
	DirectX::XMVECTOR maxPoint, minPoint;
	SceneManager::sGetInstance()->createModel(*this, "Objects\\SM_construction_fence_01a", L"Objects\\TX_ConstructionFence_01a_ALB", maxPoint, minPoint);
	mTransform->setPosition(position);
	mTransform->setScale(scale);

	DirectX::XMFLOAT3 maxP(1.86109996f, 211.244995f, 1.88594997f);
	DirectX::XMFLOAT3 minP(-305.583008f, 0.000000000f, -2.35370994f);
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

SM_construction_fence::~SM_construction_fence()
{
}

BoundingCube * SM_construction_fence::getCollisionBox()
{
	return mCollisionBox;
}

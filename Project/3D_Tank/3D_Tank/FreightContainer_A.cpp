#include "FreightContainer_A.h"
#include "GameCommon.h"

FreightContainer_A::FreightContainer_A(const Vector3& position, const Vector3& rotate, const Vector3& scale, const int& textureNum)
{
	DirectX::XMVECTOR maxPoint, minPoint;
	if(textureNum == 0)
		SceneManager::sGetInstance()->createModel(*this, "Objects\\SM_FreightContainer_01", L"Objects\\TX_FreightContainer_01a_ALB", maxPoint, minPoint);
	else
		SceneManager::sGetInstance()->createModel(*this, "Objects\\SM_FreightContainer_01", L"Objects\\TX_FreightContainer_01b_ALB", maxPoint, minPoint);
	mTransform->setPosition(position);
	mTransform->setScale(scale);

	DirectX::XMFLOAT3 maxP(293.290009f, 261.213013f, 121.915001f);
	DirectX::XMFLOAT3 minP(-330.609009f, -0.0293269996f, -123.653000f);
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

FreightContainer_A::~FreightContainer_A()
{
}

BoundingCube * FreightContainer_A::getCollisionBox()
{
	return mCollisionBox;
}

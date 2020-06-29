#include "SM_WaterTank.h"
#include "GameCommon.h"

SM_WaterTank::SM_WaterTank(const Vector3 & position, const Vector3 & rotate, const Vector3 & scale)
{
	DirectX::XMVECTOR maxPoint, minPoint;
	SceneManager::sGetInstance()->createModel(*this, "Objects\\SM_WaterTank_01a", L"Objects\\TX_PortableWaterTank_01_ALB", maxPoint, minPoint);
	mTransform->setPosition(position);
	mTransform->setScale(scale);

	DirectX::XMFLOAT3 maxP(118.185997f, 119.725998f, 118.494003f);
	DirectX::XMFLOAT3 minP(-0.0447370000f, -0.000000000f, -0.000000000f);
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

SM_WaterTank::~SM_WaterTank()
{
}

BoundingCube * SM_WaterTank::getCollisionBox()
{
	return mCollisionBox;
}

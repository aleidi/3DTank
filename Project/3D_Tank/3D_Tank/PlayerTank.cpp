#include "PlayerTank.h"
#include "ComponentBase.h"
#include "GameCommon.h"

PlayerTank::PlayerTank()
{
	mAttribute = { 100,1000.0f,2000.0f };

	mBattery = SceneManager::sGetInstance()->createEmptyObject();
	mBattery->setName("Battery");
	mBattery->addComponent(SceneManager::sGetInstance()->createModel(*this, "Tank\\TankBattery", L"Tank\\TankTex"));
	mBattery->attach(*this);
	SceneManager::sGetInstance()->createModel(*this, "Tank\\TankBody", L"Tank\\TankTex");
	SceneManager::sGetInstance()->createModel(*this, "Tank\\TankTrack_L", L"Tank\\TankTrack");
	SceneManager::sGetInstance()->createModel(*this, "Tank\\TankTrack_R", L"Tank\\TankTrack");

	mTransform->setScale(0.002f, 0.002f, 0.002f);
}

PlayerTank::~PlayerTank()
{
}

void PlayerTank::Move(Vector3 value)
{
	mAccumulateSpd += value;
	mAccumulateSpd = Math::lerp(mAccumulateSpd, Vector3::zero, 0.5f);
	mTransform->translate(mAccumulateSpd);

	value = value.normalize();
	float rad = Vector3::dot(mTransform->Forward, value);
	mAccumulateRot += acosf(rad);
	mAccumulateRot = Math::lerp(mAccumulateRot, 0.0f, 0.5f);
	mTransform->rotateY(mAccumulateRot, false);
}

void PlayerTank::RotateBattery(float valueX, float valueY)
{
	mAccumulateRotBX += valueX;
	mAccumulateRotBX = Math::lerp(mAccumulateRotBX, 0.0f, 0.5f);
	mBattery->getTransform()->rotateX(mAccumulateRotBX, false);

	mAccumulateRotBY += valueY;
	mAccumulateRotBY = Math::lerp(mAccumulateRotBY, 0.0f, 0.5f);
	mBattery->getTransform()->rotateY(mAccumulateRotBY, false);
}

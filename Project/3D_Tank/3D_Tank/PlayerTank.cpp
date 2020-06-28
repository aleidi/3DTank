#include <DirectXMath.h>
#include "PlayerTank.h"
#include "ComponentBase.h"
#include "GameCommon.h"
#include "PlayerCamera.h"

PlayerTank::PlayerTank()
	:mRotateSpd(30.0f),mMoveSped(1.0f),mBatteryRotSpd(1.0f), mBatteryMaxPitch(10.0f), mBatteryMinPitch(-30.0f),
	mDisToCam(0.75f),mFPCameraOffset(mTransform->Forward * 0.5f + mTransform->Up*0.1f),mFPOfssetFactorX(0.4f), mFPOfssetFactorY(0.1f),
	mCamFollowFactorX(-2.6f), mCamFollowFactorY(1.0f),
	mMaxPitchAngle(XMConvertToRadians(80.0f)),mMinPitchAngle(XMConvertToRadians(-30.0f)), 
	mFPToTPThreshold(0.7f), mMinDisToCam(0.0f),mMaxDisToCam(1.0f),
	Pawn()
{
	mName = "PlayerTank";

	mAttribute.m_MaxSpeed = mMoveSped;

	mBattery = SceneManager::sGetInstance()->createEmptyObject();
	mBattery->setName("Battery");
	SceneManager::sGetInstance()->createModel(*mBattery, "Tank\\TankBattery", L"Tank\\TankTex");
	mBattery->attach(*this);
	SceneManager::sGetInstance()->createModel(*this, "Tank\\TankBody", L"Tank\\TankTex");
	SceneManager::sGetInstance()->createModel(*this, "Tank\\TankTrack_L", L"Tank\\TankTrack");
	SceneManager::sGetInstance()->createModel(*this, "Tank\\TankTrack_R", L"Tank\\TankTrack");

	mCamFollower = SceneManager::sGetInstance()->createCube();
	mCamFollower->getTransform()->setScale(0.1f, 0.1f, 0.1f);
	mCamFollower->setName("CameraFollower");
	mCamera = SceneManager::sGetInstance()->createEmptyObject();
	mCamera->setName("CameraObj");
	mCameraComp = new PlayerCamera(mCamera);
	mCamera->addComponent(mCameraComp);
	mCamera->attach(*mCamFollower);
	mCamera->getTransform()->translate(mTransform->getPosition() + 
		mCamFollower->getTransform()->Forward * mCamFollowFactorX + mCamFollower->getTransform()->Up * mCamFollowFactorY * mDisToCam);
	mTransform->setScale(0.002f, 0.002f, 0.002f);

	//t1 = SceneManager::sGetInstance()->createSphere();
	//t1->attach(*mCamFollower);
	//t1->getTransform()->translate(Vector3::right * 2.0f);
}

PlayerTank::~PlayerTank()
{
	mBattery->destroy();
	mBattery = nullptr;
	mCamFollower->destroy();
	mCamFollower = nullptr;
	mCamera->destroy();
	mCamera = nullptr;
	mCameraComp = nullptr;
}

void PlayerTank::onUpdate(float deltaTime)
{
	Pawn::onUpdate(deltaTime);

}

void PlayerTank::onLateUpdate(float deltaTime)
{
	Pawn::onLateUpdate(deltaTime);

	Vector3 v = Math::lerp(mBattery->getTransform()->getRotation(), mCamFollower->getTransform()->getRotation(), deltaTime*mBatteryRotSpd);
	mBattery->getTransform()->setRotation(v);
	Vector3 rot = mBattery->getTransform()->getRotation();
	if (rot.x > XMConvertToRadians(mBatteryMaxPitch))
	{
		rot.x = XMConvertToRadians(mBatteryMaxPitch);
		mBattery->getTransform()->setRotation(rot);
	}
	if (rot.x < XMConvertToRadians(mBatteryMinPitch))
	{
		rot.x = XMConvertToRadians(mBatteryMinPitch);
		mBattery->getTransform()->setRotation(rot);
	}

	mCamFollower->getTransform()->setPosition(mTransform->getPosition() + mFPCameraOffset);
}

void PlayerTank::move(Vector3 value)
{
	mTransform->translate(value * mMoveSped);
	m_Velocity = value;
}

void PlayerTank::rotate(float value)
{
	mTransform->rotateY(value * mRotateSpd);
}

void PlayerTank::rotateCamera(float valueX, float valueY)
{
	float angle = mCamFollower->getTransform()->getRotation().x;
	if (angle > mMaxPitchAngle)
	{
		valueX = -0.01f;
	}
	else if (angle < mMinPitchAngle)
	{
		valueX = 0.01f;
	}
	mCamFollower->getTransform()->rotate(valueX*60.0f, valueY*60.0f,0.0f);


	std::wstring wstr = L"Rotation:";
	wstr += std::to_wstring(mCamFollower->getTransform()->getRotation().x) + L"," + std::to_wstring(mCamFollower->getTransform()->getRotation().y) +
		L"," + std::to_wstring(mCamFollower->getTransform()->getRotation().z);
	//Engine::sGetInstance()->showtText(wstr, 100, 100, 500, 500, true);

}

void PlayerTank::adjustDisToCam(float value)
{
	mDisToCam += value;
	Math::Clamp(mMaxDisToCam, mMinDisToCam, mDisToCam);
	Vector3 dir = mCamFollower->getTransform()->Forward * mCamFollowFactorX + mCamFollower->getTransform()->Up * mCamFollowFactorY;
	if (mDisToCam > mFPToTPThreshold)
	{
		mFPCameraOffset = Vector3::zero;
		mCamera->getTransform()->setPosition(mTransform->getPosition() + dir * mDisToCam);
	}
	else if (mDisToCam <= mFPToTPThreshold)
	{
		mFPCameraOffset = mTransform->Forward * mFPOfssetFactorX + mTransform->Up * mFPOfssetFactorY;
		mCamera->getTransform()->setPosition(mTransform->getPosition() + mFPCameraOffset + dir * mDisToCam);
	}

	//std::wstring wstr = L"Position:";
	//wstr += std::to_wstring(mBattery->getTransform()->getRotation().x) + L"," + std::to_wstring(mBattery->getTransform()->getRotation().y) +
	//	L"," + std::to_wstring(mBattery->getTransform()->getRotation().z);
}

void PlayerTank::setCameraFov(float value)
{
	mCameraComp->setFov(value);
}

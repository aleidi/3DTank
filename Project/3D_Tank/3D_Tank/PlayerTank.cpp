#include <DirectXMath.h>
#include "PlayerTank.h"
#include "ComponentBase.h"
#include "GameCommon.h"
#include "CollisionManager.h"
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

	DirectX::XMVECTOR maxPoint, minPoint;
	mBattery = SceneManager::sGetInstance()->createEmptyObject();
	mBattery->setName("Battery");
	mBattery->addComponent(SceneManager::sGetInstance()->createModel(*mBattery, "Tank\\TankBattery", L"Tank\\TankTex", maxPoint, minPoint));
	mBattery->attach(*this);
	DirectX::XMFLOAT3 maxP(93.4250031f, 210.244995f, 299.684998f);
	DirectX::XMFLOAT3 minP(-71.5699997f, 70.3600006f, -106.195000f);
	maxPoint = DirectX::XMLoadFloat3(&maxP); minPoint = DirectX::XMLoadFloat3(&minP);
	BoundingCube* batteryBoundingCube = new BoundingCube(mBattery);
	batteryBoundingCube->createBoundingCube(maxPoint, minPoint, 1);
	mBattery->addComponent(batteryBoundingCube);
	SceneManager::sGetInstance()->createModel(*this, "Tank\\TankBody", L"Tank\\TankTex", maxPoint, minPoint);
	DirectX::XMFLOAT3 maxP0(108.550003f, 97.2149963f, 177.554993f);
	DirectX::XMFLOAT3 minP0(-86.8899994f, 3.51500010f, -191.240005f);
	maxPoint = DirectX::XMLoadFloat3(&maxP0); minPoint = DirectX::XMLoadFloat3(&minP0);
	BoundingCube* bodyBoundingCube = new BoundingCube(this);
	bodyBoundingCube->createBoundingCube(maxPoint, minPoint, 1);
	this->addComponent(bodyBoundingCube);
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
	mTransform->calcultateTransformMatrix();
	DirectX::BoundingOrientedBox out;
	bodyBoundingCube->box.Transform(out, mTransform->getLocalToWorldMatrix());
	bodyBoundingCube->box = out;
	this->cube = bodyBoundingCube;
	DirectX::BoundingOrientedBox out1;
	batteryBoundingCube->box.Transform(out1, mTransform->getLocalToWorldMatrix());
	batteryBoundingCube->box = out1;
	mBattery->cube = batteryBoundingCube;
	//t1 = SceneManager::sGetInstance()->createSphere();
	//t1->attach(*mCamFollower);
	//t1->getTransform()->translate(Vector3::right * 2.0f);
	moveDirection = FORWARD;
}

PlayerTank::~PlayerTank()
{
	mBattery = nullptr;
	mCamFollower = nullptr;
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

void PlayerTank::onTriggerEnter(const GameObject* obj)
{
	this->onTrigger = true;
	switch (moveDirection) {
	case FORWARD: {
		move(mTransform->Forward * -0.01f);
		break;
	}
	case MBACK: {
		move(mTransform->Forward * 0.01f);
		break;
	}
	case LEFT: {
		rotate(0.001f);
		break;
	}
	case RIGHT: {
		rotate(-0.001f);
		break;
	}
	}
	if (CollisionManager::sGetInstance()->collisionCheck(this->cube, obj->cube) == false)
		onTriggerExit();
}

void PlayerTank::onTriggerExit()
{
	this->onTrigger = false;
}

void PlayerTank::onCollisionEnter(const GameObject* obj)
{
	
}

void PlayerTank::onCollisionExit()
{

}

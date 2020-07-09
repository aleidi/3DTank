#include <DirectXMath.h>
#include "PlayerTank.h"
#include "ComponentBase.h"
#include "GameCommon.h"
#include "CollisionManager.h"
#include "PlayerCamera.h"
#include "HUD.h"
#include "Shell.h"
#include "ShellFlyComponent.h"
#include "ParticleSystem.h"
#include "ShellContainer.h"
#include "SoundComponent.h"
#include "SoundManager.h"

PlayerTank::PlayerTank()
	:mRotateSpd(30.0f),mMoveSped(1.0f),mBatteryRotSpd(1.0f), mBatteryMaxPitch(10.0f), mBatteryMinPitch(-30.0f),
	mDisToCam(0.75f),mFPCameraOffset(mTransform->Forward * 0.5f + mTransform->Up*0.1f),mFPOfssetFactorX(0.4f), mFPOfssetFactorY(0.1f),
	mCamFollowFactorX(-2.6f), mCamFollowFactorY(1.0f),
	mMaxPitchAngle(XMConvertToRadians(80.0f)),mMinPitchAngle(XMConvertToRadians(-30.0f)), 
	mFPToTPThreshold(0.7f), mMinDisToCam(0.0f),mMaxDisToCam(1.0f), mCameraRotSpd(60.0f)
{
	mTag = ObjectTag::Player;
	mName = "PlayerTank";

	mAttribute.m_MaxSpeed = mMoveSped;

	DirectX::XMVECTOR maxPoint, minPoint;
	mBattery = SceneManager::sGetInstance()->createEmptyObject();
	mBattery->setName("Battery");
	SceneManager::sGetInstance()->createModel(*mBattery, "Tank\\TankBattery", L"Tank\\TankTex");
	SceneManager::sGetInstance()->createModel(*this, "Tank\\TankBody", L"Tank\\TankTex", maxPoint, minPoint);
	DirectX::XMFLOAT3 maxP0(108.550003f, 97.2149963f, 177.554993f);
	DirectX::XMFLOAT3 minP0(-86.8899994f, 3.51500010f, -191.240005f);
	maxPoint = DirectX::XMLoadFloat3(&maxP0); minPoint = DirectX::XMLoadFloat3(&minP0);
	BoundingCube* bodyBoundingCube = new BoundingCube(this);
	bodyBoundingCube->createBoundingCube(maxPoint, minPoint, 1);
	this->addComponent(bodyBoundingCube);
	SceneManager::sGetInstance()->createModel(*this, "Tank\\TankTrack_L", L"Tank\\TankTrack");
	SceneManager::sGetInstance()->createModel(*this, "Tank\\TankTrack_R", L"Tank\\TankTrack");

	mCamFollower = SceneManager::sGetInstance()->createEmptyObject();
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
	mBattery->getTransform()->setScale(0.002f, 0.002f, 0.002f);
	mTransform->calcultateTransformMatrix();
	DirectX::BoundingOrientedBox out;
	bodyBoundingCube->box.Transform(out, mTransform->getLocalToWorldMatrix());
	bodyBoundingCube->box = out;
	this->cube = bodyBoundingCube;
	tankSound = new SoundComponent(this);
	this->addComponent(tankSound);


	moveDirection = FORWARD;
	rotateDirection = MRIGHT;

	mHUD = new HUD();

	mAttribute.m_HP = 1000;
	mAttribute.FullHP = 1000;
	mAttribute.m_AttackRangeRadiusSq = 20.0f;

	mLightInterval = 0.1f;
	mHeavyInterval = 2.0f;
	mAttackCount = mLightInterval;
	mAttackAngle = DirectX::XMConvertToRadians(60);

	initParticle();
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
	SceneManager::sGetInstance()->removeParticleFromPool(mPSAttack);
	mPSAttack = nullptr;
	SceneManager::sGetInstance()->removeParticleFromPool(mPSHited);
	mPSHited = nullptr;

}

void PlayerTank::onUpdate(const float& deltaTime)
{
	Pawn::onUpdate(deltaTime);

	if (DInputPC::getInstance().iskeyDown(DIK_F3))
	{
		playHitedParticle();
	}
	SoundManager::sGetInstance()->setLisenterPosition(mTransform->getPosition());
}

void PlayerTank::onLateUpdate(const float& deltaTime)
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

void PlayerTank::destroy()
{
	SceneManager::sGetInstance()->removeGameObjectFromPool(this);
}

void PlayerTank::onAttack(float deltaTime)
{
	mAttackCount -= deltaTime;
	if (mAttackCount <= 0.0f)
	{
		float randX = (float)rand() / (float)RAND_MAX * 0.2f - 0.1f;
		float randY = (float)rand() / (float)RAND_MAX * 0.2f - 0.1f;
		float randZ = (float)rand() / (float)RAND_MAX * 0.2f - 0.1f;
		Vector3 offset = Vector3(randX, randY, randZ);
		Vector3 startPos = mBattery->getTransform()->getPosition() + offset;

		//detect enemy whether can be attacked
		Vector3 origin = mCamera->getTransform()->getPosition();
		Vector3 dir = mCamera->getTransform()->Forward;
		GameObject* col = nullptr;
		float dis = 0.0f;
		CollisionManager::sGetInstance()->rayCheck(origin, dir, mAttribute.m_AttackRangeRadiusSq, &col, dis);
		if(col != nullptr && col->getTag() == GameObject::ObjectTag::Enemy)
		{
			dir = col->getTransform()->getPosition() - startPos;
			dir = dir.normalize();
			float angle = Vector3::dot(dir, mBattery->getTransform()->Forward);
			if (angle < mAttackAngle)
			{
				playAttackParticle();
				ShellContainer::sGetInstance()->applyShell(startPos, dir, 0, 0);
			}
			else
			{
				playAttackParticle();

				ShellContainer::sGetInstance()->applyShell(startPos, mBattery->getTransform()->Forward + Vector3::up*0.02f, 0, 0);
			}
		}
		else
		{
			playAttackParticle();
			ShellContainer::sGetInstance()->applyShell(startPos, mBattery->getTransform()->Forward + Vector3::up*0.02f, 0, 0);
		}

		if (mWeaponType == WeaponType::Light)
		{
			//do light attack
			mAttackCount = mLightInterval;
		}
		else if (mWeaponType == WeaponType::Heavy)
		{
			//do heavy attack
			mAttackCount = mHeavyInterval;
		}
	}
}

void PlayerTank::setAttack()
{
	reinterpret_cast<HUD*>(mHUD)->setAccelator(130.0f, 20.0f);
}

void PlayerTank::stopAttack()
{
	reinterpret_cast<HUD*>(mHUD)->setAccelator(1.0f, 1.0f);
}

void PlayerTank::setWeaponType(WeaponType type)
{
	mWeaponType = type;
}

void PlayerTank::move(Vector3 value)
{
	mTransform->translate(value * mMoveSped);
	mBattery->getTransform()->translate(value * mMoveSped);
	m_Velocity = value;
	SoundManager::sGetInstance()->playSingleSound(tankSound->mChannel, 5);
	SoundManager::sGetInstance()->setValume(0.3, tankSound->mChannel);
	mBatteryRotSpd = 1.0f;
}

void PlayerTank::stopMove()
{
	SoundManager::sGetInstance()->stop(tankSound->mChannel);
	mBatteryRotSpd = 2.0f;
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
	mCamFollower->getTransform()->rotate(valueX*mCameraRotSpd, valueY*mCameraRotSpd,0.0f);
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

void PlayerTank::setCameraRotSpd(float value)
{
	mCameraRotSpd = value;
}

void PlayerTank::translate(float x, float y, float z)
{
	mTransform->translate(x, y, z);
	mBattery->getTransform()->translate(x, y, z);
}

void PlayerTank::hited(int value)
{
	Pawn::hited(value);
	playHitedParticle();
}

void PlayerTank::onTriggerEnter(const GameObject* obj)
{
	this->onTrigger = true;
	switch (moveDirection) {
	case FORWARD: {
		move(mTransform->Forward * -0.001f);
		break;
	}
	case MBACK: {
		move(mTransform->Forward * 0.001f);
		break;
	}
	}
	switch (rotateDirection) {
	case MLEFT: {
		rotate(0.001f);
		if (CollisionManager::sGetInstance()->collisionCheck(this->mTransform->getPosition(), this->mTransform->Forward, obj->cube) == true) {
			move(mTransform->Forward * -0.001f);
			break;
		}
		else {
			move(mTransform->Forward * 0.001f);
			break;
		}
	}
	case MRIGHT: {
		rotate(-0.001f);
		if (CollisionManager::sGetInstance()->collisionCheck(this->mTransform->getPosition(), this->mTransform->Forward, obj->cube) == true) {
			move(mTransform->Forward * -0.001f);
			break;
		}
		else {
			move(mTransform->Forward * 0.001f);
			break;
		}
	}
	}
	//case LEFT: {
	//	rotate(0.001f);
	//	break;
	//}
	//case RIGHT: {
	//	rotate(-0.001f);
	//	break;
	//}
	if (CollisionManager::sGetInstance()->collisionCheck(this->cube, obj->cube) == false)
		onTriggerExit();
}

void PlayerTank::onTriggerExit()
{
	this->onTrigger = false;
}

void PlayerTank::onCollisionEnter()
{
	hited(100);
}

void PlayerTank::onCollisionExit()
{
	
}

GameObject* PlayerTank::getBattery()
{
	return mBattery;
}

void PlayerTank::playAttackParticle()
{
	Vector3 pos = mBattery->getTransform()->getPosition() + mBattery->getTransform()->Forward * 0.8f + mBattery->getTransform()->Up * 0.1f;
	mPSAttack->setPosition(pos.x,pos.y,pos.z);
	mPSAttack->play();
}

void PlayerTank::playHitedParticle()
{
	Vector3 pos = mTransform->getPosition() + Vector3::up*0.2f;
	mPSHited->setPosition(pos.x, pos.y, pos.z);
	mPSHited->play();
}

void PlayerTank::initParticle()
{
	mPSAttack = SceneManager::sGetInstance()->createParticleSystem(L"VFX/T_Fire_Shock_01");
	mPSAttack->setTile(5.0f, 5.0f);
	mPSAttack->setEmitter(ParticleSystem::Emitter::NoEmit);
	mPSAttack->setEmitRate(1);
	mPSAttack->setLifeTime(0.3f);
	mPSAttack->setAnimationInterval(0.3f / 25.0f);
	mPSAttack->setStartScale(0.2f, 0.2f, 0.2f);
	mPSAttack->setDuration(0.3f);
	mPSAttack->setStartScale(1.0f, 1.0f, 1.0f);
	Material mat;
	mat.Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mPSAttack->setMaterial(mat);

	mPSHited = SceneManager::sGetInstance()->createParticleSystem(L"VFX/T_Fire_Shock_01");
	mPSHited->setTile(5.0f, 5.0f);
	mPSHited->setEmitter(ParticleSystem::Emitter::NoEmit);
	mPSHited->setEmitRate(1);
	mPSHited->setLifeTime(0.3f);
	mPSHited->setAnimationInterval(0.2f / 25.0f);
	mPSHited->setStartScale(0.5f, 0.5f, 0.5f);
	mPSHited->setDuration(0.3f);
	mPSAttack->setStartScale(1.0f, 1.0f, 1.0f);

}

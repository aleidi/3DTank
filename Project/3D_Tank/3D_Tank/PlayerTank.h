#pragma once
#include "Pawn.h"

class RenderComponent;
class Camera;
class ParticleSystem;

class PlayerTank : public Pawn
{
public:
	enum WeaponType
	{
		Light = 0,
		Heavy = 1,
	};
public:
	PlayerTank();
	~PlayerTank();

	void onUpdate(float deltaTime) override;
	void onLateUpdate(float deltaTime) override;
	
	
	void onAttack(float deltaTime);
	void setAttack();
	void stopAttack();
	void setWeaponType(WeaponType type);
	void move(Vector3 value) override;
	void rotate(float value);
	void rotateCamera(float valueX, float valueY);
	void adjustDisToCam(float value);
	void setCameraFov(float value);
	void setCameraRotSpd(float value);

	void hited(int value) override;
	void onTriggerEnter(const GameObject* obj) override;
	void onTriggerExit() override;
	void onCollisionEnter() override;
	void onCollisionExit() override;
	GameObject* getBattery();

private:
	void playAttackParticle();
	void playHitedParticle();
	void initParticle();

private:
	//tank move and rotate
	float mRotateSpd;
	float mMoveSped;
	float mBatteryRotSpd;
	float mBatteryMaxPitch;
	float mBatteryMinPitch;

	//camera follow paramaters
	float mDisToCam;
	Vector3 mFPCameraOffset;
	float mFPOfssetFactorX;
	float mFPOfssetFactorY;
	float mCamFollowFactorX;
	float mCamFollowFactorY;
	float mMaxPitchAngle;
	float mMinPitchAngle;
	float mFPToTPThreshold;
	float mMinDisToCam;
	float mMaxDisToCam;
	float mCameraRotSpd;

	//Weapon
	int mWeaponType;
	float mAttackCount;
	float mLightInterval;
	float mHeavyInterval;
	float mAttackAngle;

	GameObject* mBattery;
	GameObject* mCamFollower;
	GameObject* mCamera;
	Camera* mCameraComp;
	GameObject* mHUD;
	ParticleSystem* mPSAttack;
	ParticleSystem* mPSHited;
};


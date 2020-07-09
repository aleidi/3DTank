#pragma once
#include "Pawn.h"

class RenderComponent;
class SoundComponent;
class Camera;
class ParticleSystem;

class PlayerTank : public Pawn
{
public:
	PlayerTank();
	~PlayerTank();

	void onUpdate(const float& deltaTime) override;
	void onLateUpdate(const float& deltaTime) override;
	void destroy() override;

	void onAttack(float deltaTime);
	void setAttack();
	void stopAttack();
	void move(Vector3 value) override;
	void stopMove();
	void rotate(float value);
	void rotateCamera(float valueX, float valueY);
	void adjustDisToCam(float value);
	void setCameraFov(float value);
	void setCameraRotSpd(float value);
	void translate(float x, float y, float z);

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
	float mAttackInterval;
	float mAttackAngle;

	//SoundComponent* tankSound;

	GameObject* mBattery;
	GameObject* mCamFollower;
	GameObject* mCamera;
	Camera* mCameraComp;
	GameObject* mHUD;
	ParticleSystem* mPSAttack;
	ParticleSystem* mPSHited;
};


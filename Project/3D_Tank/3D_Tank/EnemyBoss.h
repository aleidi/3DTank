#pragma once
#include "EnemyTank.h"
#include "ParticleSystem.h"

class EnemyBoss : public EnemyTank
{
public:
	enum Mode
	{
		Normal = 0,
		Super = 1
	};
public:
	EnemyBoss(int id);
	~EnemyBoss();

	void showUI(bool value);
	void ChangeMode(Mode mode);
	void onLateUpdate(const float& deltaTime) override;
	void onUpdate(const float& deltaTime) override;
	void onCollisionEnter() override;
	void hited(int value) override;


	void playSuperAttackParticle();
	void enableSuperAttack(bool value);
	void enableFloat(bool value);
	void preDoSuperAttack();

	void setSuperAttackInterval(float interval);

	void initViolent(int maxParticle, int emitRate);

private:
	void initParticles() override;
	void doFloat(const float& deltaTime);
	void doSuperAttack();

private:
	GameObject* mNormalModel;
	GameObject* mSuperModel;

	UIImage* mImage;
	UIImage* mFrame;
	UIText* mName;

	float mOffsetFloat;

	ParticleSystem* mPSSuperAttack;
	bool mCanSuperAttack;
	bool mCanFloat;

	std::vector<ParticleSystem::PAttribute> mSAParticles;
	int mSAIndex;
	float mTimerSA;
	float mIntervalSA;
	Vector3 mBatteryOffset;
	UIImage3D* mFazhen;
};


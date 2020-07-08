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

	void playSuperAttackParticle();
	void enableSuperAttack(bool value);
	void enableFloat(bool value);
	void preDoSuperAttack();

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

	float mOffset;

	ParticleSystem* mPSSuperAttack;
	bool mCanSuperAttack;
	bool mCanFloat;

	std::vector<ParticleSystem::PAttribute> mSAParticles;
	int mSAIndex;
	float mTimerSA;
	float mIntervalSA;
};


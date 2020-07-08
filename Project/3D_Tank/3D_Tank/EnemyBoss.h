#pragma once
#include "EnemyTank.h"

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

	void superattack();

private:
	void initParticles() override;
	void playSuperAttackParticle();

private:
	GameObject* mNormalModel;
	GameObject* mSuperModel;

	UIImage* mImage;
	UIImage* mFrame;
	UIText* mName;

	float mOffset;

	ParticleSystem* mPSSuperAttack;
};

